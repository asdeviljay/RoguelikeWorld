// RoguelikeWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CWGame.hpp"
#include "Monster.hpp"
#include <iostream>

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

	CWGame game;

	if (!game.init()) {
		return 0;
	}

	while (true) {
		if (game.isEnd) {
			char c;
			do {
				std::cout << "Want to play again (y/n) : ";
				std::cin >> c;
			} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
			if (c == 'y' || c == 'Y') {
				game.restartGame();
				game = CWGame();
				if (!game.init()) {
					return 0;
				}
				continue;
			}
			else if (c == 'n' || c == 'N') {
				break;
			}
		} 
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
