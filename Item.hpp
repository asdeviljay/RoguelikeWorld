#pragma once

#include <string>
#include <vector>

class Item
{
public:
	Item();
	Item(int t_posX, int t_posY, unsigned int t_itemType, std::string t_name, int t_para1);
	~Item();
	Item(const Item&) = default;
	Item& operator= (const Item&) = default;

	void update();
	void useItem();
	std::vector<int> pickIt();

	const enum itemType {
		EQUIP, POTION
	};

private:
	int posX;
	int posY;

	unsigned int m_itemType;

	bool isPicked = false;

	struct EQUIP {
		std::string m_name;
		int m_increasedAttack;
	}m_equip;

	struct POTION {
		std::string m_name;
		int m_increasedHealth;
	}m_potion;
};

