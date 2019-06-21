// RoguelikeWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CWGame.hpp"
#include "Monster.hpp"
#include <iostream>
#include <map>

#define _CRTDBG_MAP_ALLOC

/*class Monster {
public:
	void print() {
		std::cout << "WTF" << std::endl;
	}
};*/

typedef std::shared_ptr<Monster> StrongMonsterPtr;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*std::map<unsigned int, StrongMonsterPtr> monsters;
	monsters.insert(std::make_pair(1, std::make_shared<Monster>()));
	monsters.insert(std::make_pair(2, std::make_shared<Monster>()));	
	monsters[4165468564]->print();*/

	/*for (auto it = monsters.begin(); it != monsters.end(); ++it) {
		it->second->print();
	}*/

	//std::cout << "WTF" << std::endl;

	CWGame game;

	if (!game.init()) {
		return 0;
	}

	while (true) {
		game.update();
	}

	game.destroy();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
