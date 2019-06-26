#include "pch.h"
#include "CWGame.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Item.hpp"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"

#define _CRT_SECURE_NO_WARNINGS

CWGame::CWGame() :
	map(std::make_shared<Map>())
{
	loadJsonFile();

	/*monsters.insert(std::make_pair(std::make_pair(5, 5), std::make_shared<Monster>(5, 5, 10, 1)));
	monsters.insert(std::make_pair(std::make_pair(10, 10), std::make_shared<Monster>(10, 10, 5, 2)));
	items.insert(std::make_pair(std::make_pair(1, 12), std::make_shared<Item>(1, 12, Item::itemType::EQUIP, "Legendary Sword", 7497121)));
	items.insert(std::make_pair(std::make_pair(22, 1), std::make_shared<Item>(22, 1, Item::itemType::POTION, "Flask from Dark Soul", 2)));*/
}

/*CWGame& CWGame::operator= (const CWGame&) {
	map = std::make_shared<Map>();
	player =std::make_shared<Player>();
	monsters[std::make_pair(5, 5)] = std::make_shared<Monster>(5, 5, 10, 1);
	monsters[std::make_pair(10, 10)] = std::make_shared<Monster>(10, 10, 5, 2);
	items[std::make_pair(1, 12)] = std::make_shared<Item>(1, 12, Item::itemType::EQUIP, "Legendary Sword", 7497121);
	items[std::make_pair(22, 1)] = std::make_shared<Item>(22, 1, Item::itemType::POTION, "Flask from Dark Soul", 2);
}*/

CWGame::~CWGame()
{
}

bool CWGame::init() {
	std::cout << "_________________________" << std::endl;
	std::cout << "|                       |" << std::endl;
	std::cout << "|       Rougelike       |" << std::endl;
	std::cout << "|        Project        |" << std::endl;
	std::cout << "|_______________________|" << std::endl;
	std::cout << "       How to play       " << std::endl;
	std::cout << " Press Arrow Key To Move " << std::endl;
	_getch();
	system("CLS");
	if (!map->init()) {
		return false;
	}
	return true;
}

void CWGame::update() {
	if (player->isDead) {
		isEnd = player->isDead;
	}
	map->update();
	player->update();
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		it->second->update();
	}
	for (auto it = items.begin(); it != items.end(); ++it) {
		it->second->update();
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
		//
		break;
	}
	this->monsterRandomWalk();
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
	}
	monsters.clear();
	for (auto it = items.begin(); it != items.end(); ++it) {
		it->second.reset();
	}
	items.clear();
	isEnd = false;
}

void CWGame::monsterRandomWalk() {
	CHAR_INFO ci;
	COORD coordSize = { 1, 1 };
	COORD coord = { 0, 0 };
	size_t breakLoop = monsters.size();
	size_t count = 0;
	for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		if (count == breakLoop) {
			break;
		}
		count++;
		srand(static_cast<unsigned int>(time(NULL)));
		int randomWalk = rand() % randomDirection;
		int keyX = it->first.first;
		int keyY = it->first.second;
		switch (randomWalk) {
		case 0:	//UP
			{
				SMALL_RECT rect = { static_cast<short>(keyX), static_cast<short>(keyY - 1), static_cast<short>(keyX), static_cast<short>(keyY - 1) };
				ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordSize, coord, &rect);
				if (ci.Char.AsciiChar == '.') {
					it->second->changePosition(0, -1);
					std::swap(monsters[std::make_pair(keyX, keyY - 1)], it->second);
					monsters.erase(it);
					it = monsters.begin();
				}
				else {
					continue;
				}
				break;
			}
		case 1:	//LEFT
			{
				SMALL_RECT rect = { static_cast<short>(keyX - 1), static_cast<short>(keyY), static_cast<short>(keyX - 1), static_cast<short>(keyY) };
				ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordSize, coord, &rect);
				if (ci.Char.AsciiChar == '.') {
					it->second->changePosition(-1, 0);
					std::swap(monsters[std::make_pair(keyX - 1, keyY)], it->second);
					monsters.erase(it);
					it = monsters.begin();
				}
				else {
					continue;
				}
				break;
			}
		case 2:	//RIGHT
			{
				SMALL_RECT rect = { static_cast<short>(keyX + 1), static_cast<short>(keyY), static_cast<short>(keyX + 1), static_cast<short>(keyY) };
				ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordSize, coord, &rect);
				if (ci.Char.AsciiChar == '.') {
					it->second->changePosition(1, 0);
					std::swap(monsters[std::make_pair(keyX + 1, keyY)], it->second);
					monsters.erase(it);
					it = monsters.begin();
				}
				else {
					continue;
				}
				break;
			}
		case 3:	//DOWN
			{
				SMALL_RECT rect = { static_cast<short>(keyX), static_cast<short>(keyY + 1), static_cast<short>(keyX), static_cast<short>(keyY + 1) };
				ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordSize, coord, &rect);
				if (ci.Char.AsciiChar == '.') {
					it->second->changePosition(0, 1);
					std::swap(monsters[std::make_pair(keyX, keyY + 1)], it->second);
					monsters.erase(it);
					it = monsters.begin();
				}
				else {
					continue;
				}
				break;
			}
		default:
			break;
		}
	}
}

void CWGame::loadJsonFile() {

	std::ifstream ifs(jsonFileName);
	jsonFile = nlohmann::json::parse(ifs);
	//std::cout << jsonFile.dump();

	//std::cout << "<<< " << jsonFile["player"]["posX"];

	player = std::make_shared<Player>(
		static_cast<int>(jsonFile["player"]["posX"]),
		static_cast<int>(jsonFile["player"]["posY"]),
		static_cast<int>(jsonFile["player"]["healthPoint"]),
		static_cast<int>(jsonFile["player"]["attackPoint"])
		);

	monsters.insert(
		std::make_pair(
			std::make_pair(
				static_cast<int>(jsonFile["monster"]["0"]["posX"]), 
				static_cast<int>(jsonFile["monster"]["0"]["posY"])
			), std::make_shared<Monster>(
				static_cast<int>(jsonFile["monster"]["0"]["posX"]), 
				static_cast<int>(jsonFile["monster"]["0"]["posY"]), 
				static_cast<int>(jsonFile["monster"]["0"]["healthPoint"]),
				static_cast<int>(jsonFile["monster"]["0"]["attackPoint"]))
			)
		);
	monsters.insert(
		std::make_pair(
			std::make_pair(
				static_cast<int>(jsonFile["monster"]["1"]["posX"]),
				static_cast<int>(jsonFile["monster"]["1"]["posY"])
			), std::make_shared<Monster>(
				static_cast<int>(jsonFile["monster"]["1"]["posX"]),
				static_cast<int>(jsonFile["monster"]["1"]["posY"]),
				static_cast<int>(jsonFile["monster"]["1"]["healthPoint"]),
				static_cast<int>(jsonFile["monster"]["1"]["attackPoint"]))
		)
	);

	items.insert(
		std::make_pair(
			std::make_pair(
				static_cast<int>(jsonFile["item"]["0"]["posX"]),
				static_cast<int>(jsonFile["item"]["0"]["posY"])
			), std::make_shared<Item>(
				static_cast<int>(jsonFile["item"]["0"]["posX"]),
				static_cast<int>(jsonFile["item"]["0"]["posY"]),
				(jsonFile["item"]["0"]["itemType"] == "EQUIP") ? Item::itemType::EQUIP : Item::itemType::POTION,
				jsonFile["item"]["0"]["name"],
				static_cast<int>(jsonFile["item"]["0"]["para1"]))
			)
		);
	items.insert(
		std::make_pair(
			std::make_pair(
				static_cast<int>(jsonFile["item"]["1"]["posX"]),
				static_cast<int>(jsonFile["item"]["1"]["posY"])
			), std::make_shared<Item>(
				static_cast<int>(jsonFile["item"]["1"]["posX"]),
				static_cast<int>(jsonFile["item"]["1"]["posY"]),
				(jsonFile["item"]["1"]["itemType"] == "EQUIP") ? Item::itemType::EQUIP : Item::itemType::POTION,
				jsonFile["item"]["1"]["name"],
				static_cast<int>(jsonFile["item"]["1"]["para1"]))
		)
	);
}