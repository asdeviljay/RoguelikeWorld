#include "pch.h"
#include "CWGame.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Item.hpp"
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS

CWGame::CWGame() :
	map(std::make_shared<Map>()),
	player(std::make_shared<Player>())
{
	monsters[std::make_pair(5, 5)] = std::make_shared<Monster>(5, 5, 10, 1);
	monsters[std::make_pair(10, 10)] = std::make_shared<Monster>(10, 10, 5, 2);
	items[std::make_pair(1, 12)] = std::make_shared<Item>(1, 12, Item::itemType::EQUIP, "Legendary Sword", 7497121);
	items[std::make_pair(22, 1)] = std::make_shared<Item>(22, 1, Item::itemType::POTION, "Flask from Dark Soul", 2);
}


CWGame::~CWGame()
{
}

bool CWGame::init() {
	if (!map->init()) {
		return false;
	}
	return true;
}

void CWGame::update() {
	if (player->isDead) {
		isEnd = player->isDead;
	}
	switch (_getch()) {
	case CWGame::UP:
		checkWalkable(player->getPositionX(), player->getPositionY() - 1);
		break;
	case CWGame::LEFT:
		checkWalkable(player->getPositionX() - 1, player->getPositionY());
		break;
	case CWGame::RIGHT:
		checkWalkable(player->getPositionX() + 1, player->getPositionY());
		break;
	case CWGame::DOWN:
		checkWalkable(player->getPositionX(), player->getPositionY() + 1);
		break;
	default:
		break;
	}
	
	

	map->update();
	player->update();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		it->second->update();
	}
	for (auto it = items.begin(); it != items.end(); ++it) {
		it->second->update();
	}
	player->reportStatus();

	if (isEnd && !player->isDead) {
		system("CLS");
		std::cout << "Congratulation you win the game!" << std::endl;
	}
}

void CWGame::destroy() {
	map->destroy();
}

void CWGame::checkWalkable(const int& t_posX, const int& t_posY) {
	
	CHAR_INFO ci;
	COORD coordSize = { 1, 1 };
	COORD coord = { 0, 0 };
	SMALL_RECT rect = { static_cast<short>(t_posX), static_cast<short>(t_posY), static_cast<short>(t_posX), static_cast<short>(t_posY) };
	char seen = ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordSize, coord, &rect) ? ci.Char.AsciiChar : '\0';
	system("CLS");
	switch (seen)
	{
	case '.':
		player->setPositionX(t_posX);
		player->setPositionY(t_posY);
		break;
	case 'M':
		monsters[std::make_pair(t_posX, t_posY)]->takeDamage(player->getAttackPoint());
		player->setHealthPoint(player->getHealthPoint() - monsters[std::make_pair(t_posX, t_posY)]->doDamage());
		monsters[std::make_pair(t_posX, t_posY)]->reportStatus();
		break;
	case 'I':
		{
			std::vector<int> itemEffect = items[std::make_pair(t_posX, t_posY)]->pickIt();
			if (itemEffect[0] == 0) {
				player->setAttackPoint(player->getAttackPoint() + itemEffect[1]);
			}
			if (itemEffect[0] == 1) {
				player->setHealthPoint(player->getHealthPoint() + itemEffect[1]);
			}
			itemEffect.clear();
		}
		break;
	case 'D':
		player->setPositionX(t_posX);
		player->setPositionY(t_posY);
		break;
	case 'E':
		isEnd = true;
		break;
	default:
		break;
	}
}

void CWGame::restartGame() {
	map.reset();
	player.reset();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		it->second.reset();
		//monsters.erase(it->first);
	}
	monsters.clear();
	isEnd = false;
	//CWGame::CWGame();
	//return CWGame::init();
}