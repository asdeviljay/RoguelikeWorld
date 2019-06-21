#pragma once

#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y) {
	//printf("%c[%d;%df", 0x1B, y, x);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void isWalkable(int x, int y) {
	//if(x + 1 == )
}

char getCharxy(int x, int y) {
	CHAR_INFO ci;
	COORD coord = { 0, 0 };
	SMALL_RECT rect = { static_cast<short>(x), static_cast<short>(y), static_cast<short>(x), static_cast<short>(y) };
	return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coord, coord, &rect) ? ci.Char.AsciiChar : '\0';
}