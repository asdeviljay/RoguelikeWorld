#include "pch.h"
#include "CWGame.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

CWGame::CWGame() :
	map(std::make_shared<Map>()),
	player(std::make_shared<Player>())
{
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
	switch (_getch()) {
	case CWGame::UP:
		player->setPositionY(player->getPositionY() - 1);
		break;
	case CWGame::LEFT:
		player->setPositionX(player->getPositionX() - 1);
		break;
	case CWGame::RIGHT:
		player->setPositionX(player->getPositionX() + 1);
		break;
	case CWGame::DOWN:
		player->setPositionY(player->getPositionY() + 1);
		break;
	default:
		break;
	}

	system("CLS");
	map->update();
	player->update();
}

void CWGame::destroy() {
	map->destroy();
}