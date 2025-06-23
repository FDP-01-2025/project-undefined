#include "utils/menu.h"
#include "utils/consoleUtils.h"
#include <iostream>
#include <windows.h>

using namespace std;

void showMenu() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Estilo verde brillante
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    string title = "=== MENU PRINCIPAL ===";
    string opt1 = "1. Empezar";
    string opt2 = "ESC. Salir del juego";
    string prompt = "Seleccione una opcion: ";

    int y = 5;  // línea donde empiezas

    moveCursor((WINDOW_HEIGHT - title.size()) / 2, y);
    cout << title;

    moveCursor((WINDOW_HEIGHT - opt1.size()) / 2, y + 2);
    cout << opt1;

    moveCursor((WINDOW_HEIGHT - opt2.size()) / 2, y + 3);
    cout << opt2;

    moveCursor((WINDOW_HEIGHT - prompt.size()) / 2, y + 5);
    cout << prompt;

    // Restaurar color normal
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
