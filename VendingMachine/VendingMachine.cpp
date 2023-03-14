#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include "VendingMachine.h"
#include "Functions.h"

#define ESCAPE 27
#define BACKSPACE 8

const short VendingMachine::SnackShift = 5;
const short VendingMachine::MenuColWidth = 30;
const short VendingMachine::HShift = 5;
const short VendingMachine::VShift = 5;
const short VendingMachine::HelpHeight = 4;

const string VendingMachine::HELP =
"Press Esc to quit\n"
"Press 'c' to clear menu\n"
"Press 'u' to update assortment\n"
"Enter a number of position to get snack";

VendingMachine::VendingMachine(u_char Cols, u_char Rows, u_short SlotCapacity = 10)
{
	H = GetStdHandle(STD_OUTPUT_HANDLE);
	this->Cols = Cols;
	this->Rows = Rows;
	this->SlotCapacity = SlotCapacity;
	CountOfSlots = static_cast<u_short>(Rows) * Cols;
	Items = new vector<Snack>[CountOfSlots];
	MenuPos = { HShift, VShift };

	MachinePos = { HShift,
					static_cast<short>(VShift * 2 + Rows + 1) };

	TerminalPos = { static_cast<short>(MachinePos.X + LeftWidth + ElementWidth * Cols),
					static_cast<short>(MachinePos.Y + TopHeight + (ElementHeight + 1) * Rows / 3) };

	SnackPos = { static_cast<short>(MachinePos.X + LeftWidth + ElementWidth * Cols / 3),
					static_cast<short>(MachinePos.Y + TopHeight + (ElementHeight + 1) * Rows + BottomHeight + SnackShift) };

	short X = Cols * MenuColWidth + 5;
	short Y = SnackPos.Y + 15;
	SetConsoleScreenBufferSize(H, { X, Y });
}

VendingMachine::~VendingMachine()
{
	delete[] Items;
}

void VendingMachine::RunMachine()
{
	cout << HELP;
	Update();
	PrintMenu();
	PrintMachine();
	u_short digit = Digit(CountOfSlots);
	bool IsRunning = true;
	char ch;
	string Command = "";
	while (IsRunning)
	{
		if (digit == 0)
		{
			ch = _getch();
			if (ch == ESCAPE)
			{
				SetConsoleCursorPosition(H, SnackPos);
				IsRunning = false;
			}
			else
			{
				MessageBeep(MB_ICONERROR);
			}
		}
		for (u_short i = 0; i < digit; ++i)
		{
			ch = _getch();
			if (ch == ESCAPE)
			{
				SetConsoleCursorPosition(H, SnackPos);
				PrintWithShift(H, ((static_cast<string>(" ") * 32 + '\n') * 10));
				SetConsoleCursorPosition(H, SnackPos);
				IsRunning = false;
				break;
			}
			else if (ch == BACKSPACE)
			{
				if (Command.length() > 0)
				{
					MoveCursor(H, -1, 0);
					cout << '_';
					MoveCursor(H, -1, 0);
					Command.pop_back();
					i -= 2;
				}
				else
				{
					break;
				}
			}
			else if (ch == 'c' || ch == 'C')
			{
				ClearAll();
				Refresh();
				Command.clear();
				break;
			}
			else if (ch == 'u' || ch == 'U')
			{
				Update();
				Refresh();
				Command.clear();
				break;
			}
			else if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
			{
				cout << ch;
				Command += ch;
			}
			else
			{
				MessageBeep(MB_ICONERROR);
				RefreshTerminal();
				Command.clear();
				break;
			}
		}
		if (IsRunning && !Command.empty())
		{
			Dispence(stoi(Command));
			Command.clear();
		}
	}
}

void VendingMachine::Dispence(u_short pos)
{
	if (pos < CountOfSlots)
	{
		RotateSpring(pos);
		SetConsoleCursorPosition(H, SnackPos);
		PrintWithShift(H, ((static_cast<string>(" ") * 32 + '\n') * 10));
		if (!Items[pos].empty())
		{
			Items[pos].back().PrintSnack(H, this);
			Items[pos].pop_back();
			RefreshMenuPos(pos);
			MessageBeep(MB_OK);
		}
		else
		{
			MessageBeep(MB_ICONERROR);
		}
	}
	else
	{
		MessageBeep(MB_ICONERROR);
	}
	RefreshTerminal();
}

u_char VendingMachine::GetRows()
{
	return Rows;
}

u_char VendingMachine::GetCols()
{
	return Cols;
}

u_short VendingMachine::GetCountOfSlots()
{
	return CountOfSlots;
}

u_short VendingMachine::GetSlotCapacity()
{
	return SlotCapacity;
}

COORD VendingMachine::GetMachinePos()
{
	return MachinePos;
}

COORD VendingMachine::GetSnackPos()
{
	return SnackPos;
}

void VendingMachine::AddToSlot(const string &what, u_short pos, u_short count)
{
	if ((pos < CountOfSlots) &&
		(count > 0) &&
		(Items[pos].empty() || what == WhatInSlot(pos)))
	{
		for (u_short i = 0; (i < count && Items[pos].size() < SlotCapacity); ++i)
		{
			Items[pos].emplace_back(what);
		}
	}
}

void VendingMachine::Fill(const string &what, u_short pos)
{
	AddToSlot(what, pos, SlotCapacity);
}

void VendingMachine::Update()
{
	for (u_short i = 0; i < CountOfSlots; ++i)
	{
		if (!Items[i].empty())
		{
			Fill(Items[i][0].What(), i);
		}
		else
		{
			Fill(Snack::SNACKS[(rand() % Snack::SNACKS.size())], i);
		}
	}
}

void VendingMachine::RemoveFromSlot(u_short pos, u_short count)
{
	if ((pos < CountOfSlots) &&
		(count > 0) &&
		count <= Items[pos].size() &&
		!Items[pos].empty())
	{
		for (u_short i = 0; i < count; ++i)
		{
			Items[pos].pop_back();
		}
	}
}

void VendingMachine::Clear(u_short pos)
{
	Items[pos].clear();
}

void VendingMachine::ClearAll()
{
	for (u_short i = 0; i < CountOfSlots; ++i)
	{
		Items[i].clear();
	}
}

string VendingMachine::WhatInSlot(u_short pos)
{
	if (!Items[pos].empty() && (pos < CountOfSlots))
	{
		return Items[pos][0].What();
	}
	return Snack::Empty;
}

u_short VendingMachine::HowMuchIsLeft(u_short pos)
{
	if (pos < CountOfSlots)
	{
		return Items[pos].size();
	}
	return 0;
}

void VendingMachine::PrintMenu()
{
	SetConsoleCursorPosition(H, MenuPos);
	u_short X = 0;
	u_short Y = 0;
	cout << "MENU:";
	for (u_short i = 0; i < Rows; ++i)
	{
		for (u_short j = 0; j < Cols; ++j)
		{
			X = MenuPos.X + j * MenuColWidth;
			Y = MenuPos.Y + i + 1;
			PrintMenuPos(X, Y, (i * Cols + j));
		}
	}
}

void VendingMachine::PrintMachine()
{
	SetConsoleCursorPosition(H, MachinePos);
	PrintWithShift(H, LeftTop);
	for (u_char i = 0; i < Cols; ++i)
	{
		MoveCursor(H, 0, -TopHeight);
		PrintWithShift(H, Top);
	}
	MoveCursor(H, 0, -TopHeight);
	PrintWithShift(H, RightTop);
	cout << '\n';
	MoveCursor(H, MachinePos.X, 0);

	for (u_char i = 0; i < Rows; ++i)
	{
		PrintWithShift(H, Left);
		for (u_char j = 0; j < Cols; ++j)
		{
			MoveCursor(H, 0, -ElementHeight);
			PrintWithShift(H, Slot);
		}
		MoveCursor(H, 0, -ElementHeight);
		PrintWithShift(H, Right);

		cout << '\n';
		MoveCursor(H, MachinePos.X, 0);
	}

	PrintWithShift(H, LeftBottom);
	for (u_short i = 0; i <= Cols; ++i)
	{
		MoveCursor(H, 0, -BottomHeight);
		PrintWithShift(H, ((i == 0) ? _Bottom : (i == Cols) ? Bottom_ : Bottom));
	}
	MoveCursor(H, 0, -BottomHeight);
	PrintWithShift(H, RightBottom);
	RefreshTerminal();
}

void VendingMachine::ReturnToTerminal()
{
	SetCursor(H, (TerminalPos.X + 2), (TerminalPos.Y + 2));
}

void VendingMachine::Refresh()
{
	system("cls");
	SetCursor(H, 0, 0);
	cout << HELP;
	PrintMenu();
	PrintMachine();
	ReturnToTerminal();
}

void VendingMachine::RefreshTerminal()
{
	SetConsoleCursorPosition(H, TerminalPos);
	PrintWithShift(H, Terminal);
	ReturnToTerminal();
}

void VendingMachine::RefreshMenuPos(u_short pos)
{
	u_short X = MenuPos.X + (pos % Cols) * MenuColWidth;
	u_short Y = MenuPos.Y + (pos / Cols) + 1;
	SetCursor(H, X, Y);
	cout << static_cast<string>(" ") * MenuColWidth;
	PrintMenuPos(X, Y, pos);
}

void VendingMachine::RotateSpring(u_short pos)
{
	if (pos < CountOfSlots)
	{
		u_short X;
		u_short Y;
		if (Rows == 1)
		{
			X = MachinePos.X + pos * ElementWidth + LeftWidth + 2;
			Y = MachinePos.Y + TopHeight + 2;
		}
		else
		{
			X = MachinePos.X + (pos % Cols) * ElementWidth + LeftWidth + 2;
			Y = MachinePos.Y + (pos / Cols) * (ElementHeight + 1) + TopHeight + 2;
		}
		SetCursor(H, X, Y);

		for (u_char j = 0; j < Spring.length(); ++j)
		{
			cout << Spring[j];
			SetCursor(H, X, Y);
			Sleep(100);
		}

	}

}

void VendingMachine::PrintMenuPos(u_short X, u_short Y, u_short pos)
{
	u_short digit = Digit(CountOfSlots);
	u_short width = Digit(SlotCapacity) + 1;
	SetCursor(H, X, Y);
	cout << "| " << setfill('0') << setw(digit) << pos << "-" << setfill(' ') << WhatInSlot(pos) << ":";
	SetCursor(H, (X + 17), Y);
	cout << right << setw(width) << HowMuchIsLeft(pos) << " left";
}



const string VendingMachine::LeftTop =
" _\n"
"| \n"
"| ";
const string VendingMachine::Left =
"||\n"
"||\n"
"||";
const string VendingMachine::LeftBottom =
"||\n"
"| \n"
"| \n"
"| \n"
"|_";
const string VendingMachine::_Bottom =
"___\n"
" __\n"
"|  \n"
"|__\n"
"___";
const string VendingMachine::Bottom =
"_____\n"
"_____\n"
"     \n"
"_____\n"
"_____";
const string VendingMachine::Bottom_ =
"__\n"
"_ \n"
" |\n"
"_|\n"
"__";
const string VendingMachine::RightBottom =
"|       |\n"
"        |\n"
"        |\n"
"        |\n"
"________|";
const string VendingMachine::Right =
"|       |\n"
"|       |\n"
"|       |";
const string VendingMachine::RightTop =
"________ \n"
"        |\n"
"        |";
const string VendingMachine::Top =
"_____\n"
"     \n"
"_____";
const string VendingMachine::Slot =
"     \n"
"_ / _\n"
"_____";
const string VendingMachine::Terminal =
"|_______|\n"
"| _____ |\n"
"||_____||\n"
"| 7 8 9 |\n"
"| 4 5 6 |\n"
"| 1 2 3 |\n"
"| c 0 < |\n"
"|_______|";
const string VendingMachine::Spring = "-\\|/-\\|/";

const short VendingMachine::ElementWidth = 5;
const short VendingMachine::ElementHeight = 2;
const short VendingMachine::LeftWidth = 2;
const short VendingMachine::RightWidth = 9;
const short VendingMachine::TopHeight = 2;
const short VendingMachine::BottomHeight = 4;
const short VendingMachine::TerminalHeight = 7;