#include "utils/menu.h"
#include "utils/consoleUtils.h"
#include <iostream>
#include <windows.h>
#include <string>

#define WINDOW_WIDHT 80
#define WINDOW_HEIGHT 25

using namespace std;

void drawBackground() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDHT; ++x) {
            moveCursor(x, y);

            if ((x + y) % 17 == 0) {
                // Color para estrellas (#fff3b0 → amarillo claro)
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "*";
            } else if (x == 0 || x == WINDOW_WIDHT - 1) {
                // Muros verticales (#335c67 → azul oscuro)
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                cout << "|";
            } else if (y == 0 || y == WINDOW_HEIGHT - 1) {
                // Muros horizontales
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                cout << "-";
            } else {
                cout << " ";
            }
        }
    }
}

void showMenu() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    drawBackground();

    // Texto en rojo fuerte (#9e2a2b)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

    string titleArt[] = {
        "  ____ ___ ____  ____  _____ ____  _____      _    ____ ___  ",
        " |  _ \\_ _|  _ \\|  _ \\| ____|  _ \\| ____|    / \\  |  _ \\_ _| ",
        " | | | | || | | | | | |  _| | | | |  _|     / _ \\ | | | | |  ",
        " | |_| | || |_| | |_| | |___| |_| | |___   / ___ \\| |_| | |  ",
        " |____/___|____/|____/|_____|____/|_____| /_/   \\_\\___/___|  ",
        "                       DIDESPALACE                           "
    };

    int y = 3;
    for (const string& line : titleArt) {
        moveCursor((WINDOW_WIDHT - line.length()) / 2, y++);
        cout << line;
    }

    string opt1 = "1. Empezar";
    string opt2 = "ESC. Salir del juego";
    string prompt = "";

    y += 2;

    moveCursor((WINDOW_WIDHT - opt1.size()) / 2, y++);
    cout << opt1;

    moveCursor((WINDOW_WIDHT - opt2.size()) / 2, y++);
    cout << opt2;

    moveCursor((WINDOW_WIDHT - prompt.size()) / 2, y++);
    cout << prompt;

    // Restaurar color normal
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
