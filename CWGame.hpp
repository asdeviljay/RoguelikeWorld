#pragma once

#include <memory>

class Map;

class Player;

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

private:
	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
	const enum KeyArrow {
		UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80
	};
};