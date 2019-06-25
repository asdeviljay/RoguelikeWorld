#include "pch.h"
#include "Item.hpp"
#include <iostream>
#include <Windows.h>

Item::Item()
{
}

Item::Item(int t_posX, int t_posY, unsigned int t_itemType, std::string t_name, int t_para1) :
	posX(t_posX),
	posY(t_posY),
	m_itemType(t_itemType)
{
	switch (t_itemType)
	{
	case itemType::EQUIP:
		m_equip.m_name = t_name;
		m_equip.m_increasedAttack = t_para1;
		break;
	case itemType::POTION:
		m_potion.m_name = t_name;
		m_potion.m_increasedHealth = t_para1;
		break;
	default:
		break;
	}
}

Item::~Item()
{
}


void Item::update() {
	COORD coord = { static_cast<short>(posX), static_cast<short>(posY) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (!isPicked) {
		std::cout << "I";
	}
	else {
		std::cout << ".";
	}
}

void Item::useItem() {

}

std::vector<int> Item::pickIt() {
	std::vector<int> resultEffect;
	isPicked = true;
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	coord = { csbi.srWindow.Left, csbi.srWindow.Bottom - 3 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	switch (m_itemType)
	{
	case itemType::EQUIP:
		std::cout << "You pick \"" << m_equip.m_name << "\" up.\tNow, you get " << m_equip.m_increasedAttack << " attack damage(s)." << std::endl;
		resultEffect.push_back(itemType::EQUIP);
		resultEffect.push_back(m_equip.m_increasedAttack);
		break;
	case itemType::POTION:
		std::cout << "You pick \"" << m_potion.m_name << "\" up.\tNow, you get " << m_potion.m_increasedHealth << " health(s)." << std::endl;
		resultEffect.push_back(itemType::POTION);
		resultEffect.push_back(m_potion.m_increasedHealth);
		break;
	default:
		break;
	}
	return resultEffect;
}