#pragma once
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;
class VendingMachine;

class Snack
{
public:
	Snack(const string &);
	string What();
	void PrintSnack(const HANDLE &, VendingMachine *);
	~Snack();

	static const string Empty;

	static const string SNICKERS;
	static const string BOUNTY;
	static const string Mars;
	static const string MilkyWay;
	static const string KitKat;
	static const string CocaCola;
	static const string Pepsi;
	static const string Sprite;
	static const string FANTA;
	static const string MIRINDA;
	static const string Lays;
	static const string Cheetos;

	static const vector<string> SNACKS;

private:
	string what;

	string BUTILKA();
	string BATONCHIK();
	string PACHKA();

};

