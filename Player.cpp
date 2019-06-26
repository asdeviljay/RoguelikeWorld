#include "pch.h"
#include "Player.hpp"
#include <iostream>
#include <Windows.h>

Player::Player() :
	posX(2),
	posY(2),
	m_healthPoint(10),
	m_attackPoint(1)
{
}

Player::Player(int t_posX, int t_posY, int t_healthPoint, int t_attackPoint) :
	posX(t_posX),
	posY(t_posY),
	m_healthPoint(t_healthPoint),
	m_attackPoint(t_attackPoint)
{
}

Player::~Player()
{
}


void Player::update() {
	COORD coord = { static_cast<short>(posX), static_cast<short>(posY) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (m_healthPoint != 0) {
		std::cout << "P";
	}
	else {
		isDead = true;
	}
}

int Player::getPositionX() const {
	return posX;
}

int Player::getPositionY() const {
	return posY;
}

void Player::setPositionX(const int& t_posX) {
	posX = t_posX;
}

void Player::setPositionY(const int& t_posY) {
	posY = t_posY;
}

int Player::getHealthPoint() const {
	return m_healthPoint;
}

void Player::setHealthPoint(const int& t_healthPoint) {
	if (t_healthPoint <= 0) {
		m_healthPoint = 0;
	}
	else {
		m_healthPoint = t_healthPoint;
	}
}

int Player::getAttackPoint() const {
	return m_attackPoint;
}

void Player::setAttackPoint(const int& t_attackPoint) {
	m_attackPoint = t_attackPoint;
}

void Player::reportStatus() const {
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	coord = { csbi.srWindow.Left, csbi.srWindow.Bottom - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (m_healthPoint != 0) {
		std::cout << "HP : " << m_healthPoint << "\tAtt : " << m_attackPoint << std::endl;
	}
	else {
		std::cout << "Game Over!" << std::endl;
	}
}