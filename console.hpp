/**
 *	@file		console.hpp
 *	@brief		Windows Console API applied functions declaration
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-08-06
 */

#pragma once
#ifndef OMOK_CONSOLE_HPP_
#define OMOK_CONSOLE_HPP_	///< Prevent duplication

#include <Windows.h>


const int SCREEN_X = GetSystemMetrics(SM_CXSCREEN);	///< Width of screen
const int SCREEN_Y = GetSystemMetrics(SM_CYSCREEN);	///< Height of screen


/// Constants for Console::setConsoleColor()
enum class ConsoleColor : WORD {
	BLACK				///< #000000
	, LOW_BLUE			///< #000080
	, LOW_GREEN			///< #008000
	, LOW_CYAN			///< #008080
	, LOW_RED			///< #800000
	, LOW_MAGENTA		///< #800080
	, BROWN				///< #808000
	, LIGHT_GRAY		///< #c0c0c0
	, LIGHT_GREY = 7	///< #c0c0c0
	, DARK_GRAY			///< #808080
	, DARK_GREY = 8		///< #808080
	, HIGH_BLUE			///< #0000ff
	, HIGH_GREEN		///< #00ff00
	, HIGH_CYAN			///< #00ffff
	, HIGH_RED			///< #ff0000
	, HIGH_MAGENTA		///< #ff00ff
	, YELLOW			///< #ffff00
	, WHITE				///< #ffffff
};


/// Class, Contains Console WINAPI objects
class Console
{
public:
	static void setConsoleBuffer(const SHORT x, const SHORT y);
	static void setConsoleColor(const ConsoleColor foreground = ConsoleColor::LIGHT_GRAY, const ConsoleColor background = ConsoleColor::BLACK);
	static void setConsoleFont(PWCHAR fontName, const SHORT fontSize);

	static void deleteWindowMenu(const UINT position, const UINT flag = MF_BYCOMMAND);
	static void removeWindowStyle(const LONG newStyle);

	static void clearConsole(void);
	static void moveConsoleWindow(const int x = 0, const int y = 0);

	static void hideCursor(const bool flag);
	static void moveCursor(const COORD &position);
	template <typename T> static void moveCursor(const T x, const T y) {
		COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
		moveCursor(position);
	}

	static HANDLE getHandle(void) { return hConsole; }
private:
	static HWND hWindow;
	static HANDLE hConsole;
};

#endif	// OMOK_CONSOLE_HPP_
