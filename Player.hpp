#pragma once

#include <map>

class Player
{
public:
	Player();
	~Player();
	Player(const Player&) = default;
	Player& operator= (const Player&) = default;

	void update();
	int getPositionX() const;
	int getPositionY() const;
	void setPositionX(int t_posX);
	void setPositionY(int t_posY);
	void setPosition(int t_posX, int t_posY);

private:
	int posX;
	int posY;

	int m_healthPoint;
	int m_inventory;
};