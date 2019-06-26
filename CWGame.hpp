#pragma once

#include <memory>
#include <map>

class Map;

class Player;

class Monster;

class Item;

class CWGame
{
public:
	CWGame();
	~CWGame();
	CWGame(const CWGame&) = default;
	CWGame& operator= (const CWGame&) = default;

	bool init();
	void update();
	void destroy();
	void checkWalkable(const int& t_posX, const int& t_posY);
	void restartGame();
	void monsterRandomWalk();
	void loadJsonFile();

	bool isEnd = false;


private:
	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
	std::map<std::pair<int, int>, std::shared_ptr<Monster>> monsters;
	std::map<std::pair<int, int>, std::shared_ptr<Item>> items;
	const std::string jsonFileName = "gameSetting.json";
	nlohmann::json jsonFile;
	const enum KeyArrow {
		UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80
	};
	const int randomDirection = 4;
};