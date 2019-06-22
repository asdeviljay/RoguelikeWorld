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
	//std::cout << "Character = " << getCharxy(t_posX, posY);
	if (getCharxy(t_posX, posY) == '.') {
		posX = t_posX;
	}
	else if (getCharxy(t_posX, posY) == 'M') {
		//Monster and Player get damaged
	}
}

void Player::setPositionY(int t_posY) {
	if (getCharxy(posX, t_posY) == '.') {
		posY = t_posY;
	}
	else if (getCharxy(posX, t_posY) == 'M') {
		//Monster and Player get damaged
	}
}

void Player::setPosition(int t_posX, int t_posY) {
	posX = t_posX;
	posY = t_posY;
}