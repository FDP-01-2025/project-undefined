#include "menu.h"
#include <iostream>
#include <windows.h>

using namespace std;

const int CONSOLE_WIDTH = 100; // ajusta si tu consola tiene otro ancho

void moveCursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showMenu() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Estilo verde brillante
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    string title = "=== MENU PRINCIPAL ===";
    string opt1 = "1. Empezar";
    string opt2 = "ESC. Salir del juego";
    string prompt = "Seleccione una opcion: ";

    int y = 5;  // línea donde empiezas

    moveCursor((CONSOLE_WIDTH - title.size()) / 2, y);
    cout << title;

    moveCursor((CONSOLE_WIDTH - opt1.size()) / 2, y + 2);
    cout << opt1;

    moveCursor((CONSOLE_WIDTH - opt2.size()) / 2, y + 3);
    cout << opt2;

    moveCursor((CONSOLE_WIDTH - prompt.size()) / 2, y + 5);
    cout << prompt;

    // Restaurar color normal
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
