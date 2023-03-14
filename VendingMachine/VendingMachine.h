#pragma once
#include "Snack.h"
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
class VendingMachine
{
public:
	static const string HELP;
	VendingMachine(u_char, u_char, u_short);
	~VendingMachine();
	void RunMachine();
	void Dispence(u_short);
	u_char GetRows();
	u_char GetCols();
	u_short GetCountOfSlots();
	u_short GetSlotCapacity();
	COORD GetMachinePos();
	COORD GetSnackPos();
	void AddToSlot(const string &, u_short, u_short);
	void Fill(const string &, u_short);
	void Update();
	void RemoveFromSlot(u_short, u_short);
	void Clear(u_short);
	void ClearAll();
	string WhatInSlot(u_short);
	u_short HowMuchIsLeft(u_short);

private:

	void PrintMenu();
	void PrintMachine();
	void ReturnToTerminal();
	void RefreshTerminal();
	void RefreshMenuPos(u_short);
	void Refresh();
	void PrintMenuPos(u_short, u_short, u_short);
	void RotateSpring(u_short);
	HANDLE H;
	u_char Rows, Cols;
	u_short CountOfSlots, SlotCapacity;
	vector<Snack> *Items;
	COORD MachinePos, TerminalPos, MenuPos, SnackPos;
	static const string LeftTop;
	static const string Left;
	static const string LeftBottom;
	static const string _Bottom;
	static const string Bottom;
	static const string Bottom_;
	static const string RightBottom;
	static const string Right;
	static const string RightTop;
	static const string Top;
	static const string Slot;
	static const string Terminal;
	static const string Spring;
	static const short ElementWidth, ElementHeight, LeftWidth, RightWidth, TopHeight, BottomHeight, TerminalHeight;
	static const short SnackShift;
	static const short MenuColWidth;
	static const short HShift;
	static const short VShift;
	static const short HelpHeight;
};

