#include "pch.h"
#include "Monster.hpp"
#include <iostream>
#include <Windows.h>

Monster::Monster() :
	posX(4), 
	posY(4),
	m_healthPoint(4),
	m_attackPoint(4)
{
}

Monster::Monster(int t_posX, int t_posY, int t_healthPoint, int t_attackPoint) :
	posX(t_posX),
	posY(t_posY),
	m_healthPoint(t_healthPoint),
	m_attackPoint(t_attackPoint)
{
}

Monster::~Monster()
{
}

void Monster::update() {
	COORD coord = { static_cast<short>(posX), static_cast<short>(posY) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (m_healthPoint > 0) {
		std::cout << "M";
	}
	else {
		std::cout << ".";
	}
}

void Monster::takeDamage(const int& t_damage) {
	if (m_healthPoint > t_damage) {
		m_healthPoint -= t_damage;
	}
	else {
		m_healthPoint = 0;
	}
}

int Monster::doDamage() const {
	if (m_healthPoint != 0) {
		return m_attackPoint;
	}
	else {
		return 0;
	}
}

void Monster::reportStatus() const {
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	coord = { csbi.srWindow.Left, csbi.srWindow.Bottom - 2 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (m_healthPoint != 0) {
		std::cout << "Monster HP : " << m_healthPoint << "\tAtt : " << m_attackPoint << std::endl;
	}
	else {
		std::cout << "Monster died!" << std::endl;
	}
	
}

void Monster::changePosition(const int& t_pPosX, const int& t_pPosY) {
	posX += t_pPosX;
	posY += t_pPosY;
}
