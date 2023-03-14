#pragma once
#include <Windows.h>
#include <string>
std::string operator*(const std::string &, int);
std::string &operator*=(std::string &, int);
u_short Digit(int);
void SetCursor(const HANDLE &, short, short);
void MoveCursor(const HANDLE &, short, short);
void PrintWithShift(const HANDLE &H, const std::string &, short = 0);