#include "pch.h"
#include "Player.hpp"
#include "utility.hpp"
#include <iostream>


Player::Player() :
	posX(2),
	posY(2)
{
}


Player::~Player()
{
}


void Player::update() {
	gotoxy(posX, posY);
	std::cout << "P";
}

int Player::getPositionX() const {
	return posX;
}

int Player::getPositionY() const {
	return posY;
}

void Player::setPositionX(int t_posX) {
	if (getCharxy(posX, posY) == '.') {
		posX = t_posX;
	}
	else if (getCharxy(posX, posY) == 'M') {
		//Monster and Player get damaged
	}
}

void Player::setPositionY(int t_posY) {
	posY = t_posY;
}

void Player::setPosition(int t_posX, int t_posY) {
	posX = t_posX;
	posY = t_posY;
}