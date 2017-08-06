/**
 *	@file		main.cpp
 *	@brief		Omok
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-08-06
 *	@version	0.1.0
 */

#include <iostream>
#include <memory>

#include "console.hpp"
#include "game.hpp"


/// main
int main(void)
{
	std::unique_ptr<Game> game = std::make_unique<Game>();

	bool playAgain;
	do {
		Console::moveCursor(0, 0);
		game->makeBoard();
		playAgain = game->play();
	} while (playAgain);

	return 0;
}
