/**
 *	@file		game.hpp
 *	@brief		Omok game functions declaration
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-08-06
 */

#pragma once
#ifndef OMOK_GAME_HPP_
#define OMOK_GAME_HPP_	///< Prevent duplication

#include <Windows.h>

#include "console.hpp"


constexpr int BOARD_LINE = 15;	///< Each line of board

constexpr int NO_STONE = 0;		///< No stone on the board
constexpr int FIVE_STONES = 5;	///< Victory condition

constexpr int USER_BLACK = 1;	///< Player, put black stone
constexpr int USER_WHITE = -1;	///< Player, put white stone

constexpr int SEARCH_INC = 1;	///< Search for + direction
constexpr int SEARCH_DEC = -1;	///< Search for - direction


/// Constants for keyboard
enum class KEY : int {
	ESCAPE = 27		///< ESC key
	, SPACE = 32	///< Space key
	, UP = 72		///< Arrow Up key
	, LEFT = 75		///< Arrow Left key
	, RIGHT = 77	///< Arrow Right key
	, DOWN = 80		///< Arrow Down key
};


class Game
{
private:
	int board[BOARD_LINE][BOARD_LINE];
	int turn;
public:
	Game(void)
		: turn(1)
		, board{ 0, }
	{
		SetConsoleTitle(L"Omok Game");

		Console::setConsoleBuffer((BOARD_LINE + 2) * 2, BOARD_LINE + 2);
		Console::setConsoleColor(ConsoleColor::BLACK, ConsoleColor::WHITE);
		Console::setConsoleFont(L"Consolas", 22);

		Console::deleteWindowMenu(SC_RESTORE);
		Console::deleteWindowMenu(SC_MOVE);
		Console::deleteWindowMenu(SC_SIZE);
		Console::deleteWindowMenu(SC_MINIMIZE);
		Console::deleteWindowMenu(SC_MAXIMIZE);
		Console::removeWindowStyle(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);

		Console::moveConsoleWindow();
		Console::clearConsole();
		//Console::hideCursor(true);
	}

	~Game()
	{
		Console::hideCursor(false);
	}

	static void moveCursor(COORD position);
	template <typename T> static void moveCursor(T x, T y);

	int checkCondition(COORD position, int &turn, int direction, int increment);
	int checkEnd(COORD& position, int &user);

	void drawStone(int &turn);
	int pressKey(int key, COORD &position);
	bool play(void);
	static void makeBoard(void);
};

#endif	// OMOK_GAME_HPP_
