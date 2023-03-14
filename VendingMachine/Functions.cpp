#include <iostream>
#include "Functions.h"
std::string operator*(const std::string &str, int a)
{
	std::string result = "";
	for (int i = 0; i < a; ++i)
	{
		result += str;
	}
	return result;
}
std::string &operator*=(std::string &str, int a)
{
	return str = str * a;
}
u_short Digit(int a)
{
	int digit = 0;
	for (; a; a /= 10)
	{
		++digit;
	}
	return digit;
}

void SetCursor(const HANDLE &H, short x, short y)
{
	SetConsoleCursorPosition(H, { x, y });
}
void MoveCursor(const HANDLE &H, short x, short y)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(H, &info);
	SetCursor(H, (info.dwCursorPosition.X + x), (info.dwCursorPosition.Y + y));
}

void PrintWithShift(const HANDLE &H, const std::string &str, short shift)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(H, &info);
	int OriginalX = info.dwCursorPosition.X;
	int OriginalY = info.dwCursorPosition.Y;
	SetCursor(H, (OriginalX + shift), OriginalY);
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '\n')
		{
			std::cout << '\n';
			MoveCursor(H, (OriginalX + shift), 0);
		}
		else
		{
			std::cout << str[i];
		}
	}
}