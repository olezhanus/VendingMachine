#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include "VendingMachine.h"
#include "Functions.h"

using namespace std;

int main()
{
	srand(time(NULL));
	char c = 0, r = 0;
	u_short slotcap = 0;
	cout << "Enter numbers:\n";

	cout << "Number of Columns: ";
	while (!(scanf_s("%hhu", &c)))
	{
		cout << "Number of Columns: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	cout << "Number of Rows: ";
	while (!(scanf_s("%hhu", &r)))
	{
		cout << "Number of Rows: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	cout << "Number of snacks in slot: ";
	while (!(cin >> slotcap))
	{
		cout << "Number of snacks in slot: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	system("cls");
	VendingMachine *machine = new VendingMachine(c, r, slotcap);

	machine->RunMachine();

	delete machine;
	return 0;
}