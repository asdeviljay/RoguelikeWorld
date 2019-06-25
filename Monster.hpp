#pragma once
class Monster
{
public:
	Monster();
	Monster(int t_posX, int t_posY, int t_healthPoint, int t_attackPoint);
	~Monster();
	Monster(const Monster&) = default;
	Monster& operator= (const Monster&) = default;

	void update();
	void takeDamage(const int& t_damage);
	int doDamage() const;
	void reportStatus() const;
	bool comparePosition(const int& t_pPosX, const int& t_pPosY);

private:
	int posX;
	int posY;

	int m_healthPoint;
	int m_attackPoint;
};

