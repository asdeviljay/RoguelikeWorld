#pragma once
class Monster
{
public:
	Monster();
	~Monster();
	Monster(const Monster&) = default;
	Monster& operator= (const Monster&) = default;

	void update();

private:
	int posX;
	int posY;
};

