/**
 *	@file		game.cpp
 *	@brief		Omok game functions definition
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-08-06
 */

#include "game.hpp"

#include <conio.h>

#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>


void Game::moveCursor(COORD position)
{
	position.X *= 2;
	SetConsoleCursorPosition(Console::getHandle(), position);
}

template <typename T>
void Game::moveCursor(T x, T y)
{
	COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	moveCursor(position);
}


int Game::checkCondition(COORD position, int &turn, int direction, int increment)
{
	// Prevent out of range
	if (position.X < 0 || position.X >= BOARD_LINE || position.Y < 0 || position.Y >= BOARD_LINE)
		return 0;

	if (board[position.X][position.Y] != turn)
		return 0;

	switch (direction) {
		case 0: {	// Set value to check horizontal
			position.X += increment;
			break;
		}
		case 1: {	// Set value to check vertical
			position.Y += increment;
			break;
		}
		case 2: {	// Set value to check diagonal y = x
			position.X += increment;
			position.Y += increment;
			break;
		}
		case 3: {	// Set value to check diagonal y = -x
			position.X -= increment;
			position.Y += increment;
			break;
		}
	}
	return 1 + checkCondition(position, turn, direction, increment);
}

int Game::checkEnd(COORD &position, int &turn)
{
	for (int i = 0; i < 4; i++) {
		int count = -1;
		/*
		 *   x--->
		 * y +---+---+---+	// 0 for search horizontal (x= n, y=0)
		 * | |   |   |   |
		 * v +---+---+---+	// 1 for search vertical   (x= 0, y=n)
		 *   |   |   |   |
		 *   +---+---+---+	// 2 for search diagonal   (x= m, y=n)
		 *   |   |   |   |
		 *   +---+---+---+	// 3 for search diagonal   (x=-m, y=n)
		 */
		count += checkCondition(position, turn, i, SEARCH_INC);
		count += checkCondition(position, turn, i, SEARCH_DEC);
		if (count == FIVE_STONES) {
			return turn;
		}
	}
	return 0;
}

void Game::drawStone(int& turn)
{
	switch (turn) {
		case USER_BLACK:
			std::cout << "¡Ü";
			break;
		case USER_WHITE:
			std::cout << "¡Û";
			break;
	}
}

int Game::pressKey(int key, COORD &position)
{
	switch (key) {
		case static_cast<int>(KEY::UP): {
			if (position.Y > 0) {
				position.Y--;
			}
			break;
		}
		case static_cast<int>(KEY::DOWN): {
			if (position.Y < BOARD_LINE - 1) {
				position.Y++;
			}
			break;
		}
		case static_cast<int>(KEY::LEFT): {
			if (position.X > 0) {
				position.X--;
			}
			break;
		}
		case static_cast<int>(KEY::RIGHT): {
			if (position.X < BOARD_LINE - 1) {
				position.X++;
			}
			break;
		}
		case static_cast<int>(KEY::SPACE): {
			if (board[position.X][position.Y] == NO_STONE) {
				board[position.X][position.Y] = turn;	// Save value into array (Put stone)
				drawStone(turn);	// Convert value to stone shape

				if (checkEnd(position, turn)) {
					return turn;
				} else {
					turn *= -1;	// Change turn
				}
			}
			break;
		}
	}
	return 0;
}

bool Game::play(void)
{
	COORD position = { BOARD_LINE / 2, BOARD_LINE / 2 };
	do {
		moveCursor(position);
		//std::cout << "££";
		//moveCursor(position);

		if (int end = pressKey(_getch(), position)) {
			moveCursor(0, BOARD_LINE);	// Move cursor to end of BOARD_LINE
			switch (end) {
				case USER_BLACK: {
					std::cout << "--------- Black Win ---------\n";
					break;
				}
				case USER_WHITE: {
					std::cout << "--------- White Win ---------\n";
					break;

				}
			}
			std::string replay;
			std::cout << "Replay? ";
			std::getline(std::cin, replay);

			if (replay == "1"
				|| replay == "R" || replay == "r"
				|| replay == "Y" || replay == "y"
				|| replay == "YES" || replay == "yes") {
				Console::clearConsole();
				std::fill_n(&board[0][0], BOARD_LINE * BOARD_LINE, 0);	// Initialize board with 0
				return true;
			} else {
				return false;
			}
		}
	} while (true);
}

void Game::makeBoard(void)
{
	for (int i = 0; i < BOARD_LINE; i++) {	// Horizontal line of Board
		for (int j = 0; j < BOARD_LINE; j++) {	// Vertical line of Board
			switch (i) {
				case 0: {				// First Row
					switch (j) {
						case 0: {			// First Column
							std::cout << "¦£";
							break;
						}
						case BOARD_LINE - 1: {	// Last Column
							std::cout << "¦¤";
							break;
						}
						default: {			// Middle Column
							std::cout << "¦¨";
						}
					}
					break;
				}
				case BOARD_LINE - 1: {		// Last Row
					switch (j) {
						case 0: {			// First Column
							std::cout << "¦¦";
							break;
						}
						case BOARD_LINE - 1: {	// Last Column
							std::cout << "¦¥";
							break;
						}
						default: {			// Middle Column
							std::cout << "¦ª";
						}
					}
					break;
				}
				default: {				// Middle Row
					switch (j) {
						case 0: {			// First Column
							std::cout << "¦§";
							break;
						}
						case BOARD_LINE - 1: {	// Last Column
							std::cout << "¦©";
							break;
						}
						default: {			// Middle Column
							std::cout << "¦«";
						}
					}
				}
			}
		}
		std::cout << std::endl;
	}
}
