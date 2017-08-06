/**
 *	@file		console.cpp
 *	@brief		Windows Console API applied functions definition
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-08-06
 */

#include "console.hpp"


HWND Console::hWindow = GetConsoleWindow();
HANDLE Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void Console::setConsoleBuffer(const SHORT x, const SHORT y)
{
	static COORD coord;
	static SMALL_RECT rect;

	coord.X = x;
	coord.Y = y;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = coord.X - 1;
	rect.Bottom = coord.Y - 1;

	SetConsoleWindowInfo(hConsole, TRUE, &rect);
	SetConsoleScreenBufferSize(hConsole, coord);
}

void Console::setConsoleColor(const ConsoleColor foreground, const ConsoleColor background)
{
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(foreground) | static_cast<WORD>(background) << 4);
}

void Console::setConsoleFont(const PWCHAR fontName, const SHORT fontSize)
{
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 0;
	font.dwFontSize.Y = fontSize;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, fontName);

	SetCurrentConsoleFontEx(hConsole, FALSE, &font);
}


// DeleteMenu() -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms647629(v=vs.85).aspx
// WM_SYSCOMMAND -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms646360(v=vs.85).aspx
void Console::deleteWindowMenu(const UINT position, const UINT flag)
{
	HMENU hMenu = GetSystemMenu(hWindow, FALSE);

	DeleteMenu(hMenu, position, flag);

	// e.g., Delete size menu
	// DeleteMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
}

// SetWindowLong() -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms633591(v=vs.85).aspx
// Window Styles -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
void Console::removeWindowStyle(const LONG newStyle)
{
	LONG style = GetWindowLong(hWindow, GWL_STYLE);
	style = style & ~newStyle;

	SetWindowLong(hWindow, GWL_STYLE, style);

	// e.g., Disable change window size
	// SetWindowLong(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) & ~WS_SIZEBOX);

	// e.g., Remove maximize button & minimize button
	// SetWindowLong(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX));
}


void Console::clearConsole(void)
{
	CONSOLE_SCREEN_BUFFER_INFO cBuffer;
	DWORD countCell;
	COORD firstCell = { 0, 0 };
	DWORD writtenCells;

	// Get number of cells
	GetConsoleScreenBufferInfo(hConsole, &cBuffer);
	countCell = cBuffer.dwSize.X * cBuffer.dwSize.Y;

	// Fill the screen with space
	FillConsoleOutputCharacter(
		hConsole
		, static_cast<WCHAR>(' ')	// Character to write to console screen buffer
		, countCell		// Number of cells to write
		, firstCell		// Coordinate of first cell
		, &writtenCells	// Receive the number of characters written
	);

	// Get attribute of cell
	GetConsoleScreenBufferInfo(hConsole, &cBuffer);

	// Set buffer attribute
	FillConsoleOutputAttribute(
		hConsole
		, cBuffer.wAttributes	// Attribute to use when writing to console screen buffer
		, countCell		// Number of cells to write
		, firstCell		// Coordinate of first cell
		, &writtenCells	// Receive the number of characters written
	);

	// Move the cursor to first cell
	SetConsoleCursorPosition(hConsole, firstCell);
}

// SetWindowPos() -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms633545(v=vs.85).aspx
void Console::moveConsoleWindow(const int x, const int y)
{
	RECT rectangle;
	GetWindowRect(hWindow, &rectangle);
	
	int cx = rectangle.right - rectangle.left;
	int cy = rectangle.bottom - rectangle.top;

	SetWindowPos(hWindow, HWND_TOP
		, (SCREEN_X - cx) / 2 + x
		, (SCREEN_Y - cy) / 2 + y
		, cx
		, cy
		, SWP_NOZORDER | SWP_NOSIZE
	);

	// cp. SetWindowPos() & MoveWindow()
	// SetWindowPos(hWindow, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
	// MoveWindow(hWindow, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
}


void Console::hideCursor(const bool flag) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;
	cursor.bVisible = !flag;
	SetConsoleCursorInfo(hConsole, &cursor);
}

void Console::moveCursor(const COORD &position)
{
	SetConsoleCursorPosition(hConsole, position);
}
