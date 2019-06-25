#pragma once

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
	void setPositionX(const int& t_posX);
	void setPositionY(const int& t_posY);
	int getHealthPoint() const;
	void setHealthPoint(const int& t_healthPoint);
	int getAttackPoint() const;
	void setAttackPoint(const int& t_attackPoint);
	void reportStatus() const;

	bool isDead = false;

private:
	int posX;
	int posY;

	int m_healthPoint;
	int m_attackPoint;
};