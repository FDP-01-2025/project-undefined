#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>

// Configuración de la ventana
const int WINDOW_WIDHT = 100;
const int WINDOW_HEIGHT = 30;

// Colores de consola
const WORD COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD COLOR_PLAYER = FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD COLOR_BOSS = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD COLOR_STATS = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

//Funciones implementadas en consoleUtils.cpp
void consoleSettings();
void consoleCenter();
//void moveCursor(int x, int y);

#endif