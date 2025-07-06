#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <string>

// Window configuration
const int WINDOW_WIDHT = 150;
const int WINDOW_HEIGHT = 40;

// Console colors
const WORD COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD COLOR_PLAYER = FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD COLOR_BOSS = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD COLOR_STATS = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

//Functions implemented in consoleUtils.cpp
void consoleSettings();
void consoleCenter();
//Moves the cursor to a specific position on the console
void moveCursor(int x, int y);
// Change the color of the text in the console
void setColor(WORD color);
// Gets the width and height of the console
int getConsoleWidth();
int getConsoleHeight();
// Displays an animated message on the console
void showAnimatedMessage(const std::string &message, int delay = 70, int waitAfter = 1500);

#endif