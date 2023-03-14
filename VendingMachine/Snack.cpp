#include <iostream>
#include "Snack.h"
#include "VendingMachine.h"
#include "Functions.h"

Snack::Snack(const string &what)
{
	this->what = what;
}
string Snack::What()
{
	return what;
}
Snack::~Snack() {}


const string Snack::Empty = "Empty";

const string Snack::SNICKERS = "SNICKERS";
const string Snack::BOUNTY = "BOUNTY";
const string Snack::Mars = "Mars";
const string Snack::MilkyWay = "MilkyWay";
const string Snack::KitKat = "KitKat";
const string Snack::CocaCola = "CocaCola";
const string Snack::Pepsi = "Pepsi";
const string Snack::Sprite = "Sprite";
const string Snack::FANTA = "FANTA";
const string Snack::MIRINDA = "MIRINDA";
const string Snack::Lays = "Lays";
const string Snack::Cheetos = "Cheetos";

const vector<string> Snack::SNACKS { SNICKERS, BOUNTY, Mars, MilkyWay, KitKat, CocaCola, Pepsi, Sprite, FANTA, MIRINDA, Lays, Cheetos };

string Snack::BUTILKA()
{
	return
		" -_________--------_\n"
		"(                   \\______==\n"
		"(                    ______==|\n"
		"( _________        _/      ==\n"
		" -         --------\n";
}
string Snack::BATONCHIK()
{
	return
		"<\\____________________/>\n"
		"<                      >\n"
		"< ____________________ >\n"
		"</                    \\>\n";
}
string Snack::PACHKA()
{
	return
		"^^^^^^^^^^^^^^^\n"
		"\\             /\n"
		"|             |\n"
		"|             |\n"
		"|             |\n"
		"|             |\n"
		"|             |\n"
		"|             |\n"
		"/             \\\n"
		"^^^^^^^^^^^^^^^\n";
}
void Snack::PrintSnack(const HANDLE &H, VendingMachine *machine)
{
	COORD Pos = machine->GetSnackPos();
	SetConsoleCursorPosition(H, Pos);
	if (what == SNICKERS || what == BOUNTY || what == Mars || what == MilkyWay || what == KitKat)
	{
		PrintWithShift(H, BATONCHIK());
		SetCursor(H, (Pos.X + 12 - what.length() / 2), (Pos.Y + 1));
		PrintWithShift(H, what);
	}
	else if (what == CocaCola || what == Pepsi || what == Sprite || what == FANTA || what == MIRINDA)
	{
		PrintWithShift(H, BUTILKA());
		SetCursor(H, (Pos.X + 14 - what.length() / 2), (Pos.Y + 2));
		PrintWithShift(H, what);
	}
	else if (what == Lays || what == Cheetos)
	{
		PrintWithShift(H, PACHKA());
		SetCursor(H, (Pos.X + 7 - what.length() / 2), (Pos.Y + 3));
		PrintWithShift(H, what);
	}
}