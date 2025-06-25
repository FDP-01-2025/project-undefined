#include <iostream> // Entrada/salida estándar
#include <fstream> // Para leer archivos (arte ASCII)
#include <string> // Manejo de strings
#include <windows.h> // Funciones de consola en Windows
#include <conio.h> // Para capturar teclas
#include "minigames/2_spotDifference.h" // Minijuego incluido
#include "utils/consoleUtils.h" // Utilidades de consola personalizadas
using namespace std;

const int FRAME_WIDTH = 120; // Ancho del marco de batalla
const int FRAME_HEIGHT = 35; // Alto del marco de batalla

// ================= Visual Functions ===================

// Dibuja el marco principal del área de batalla
void drawBattleFrame() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int i = 0; i < FRAME_WIDTH; ++i) {
        moveCursor(5 + i, 1); cout << "-";
        moveCursor(5 + i, FRAME_HEIGHT); cout << "-";
    }
    for (int i = 1; i <= FRAME_HEIGHT; ++i) {
        moveCursor(5, i); cout << "|";
        moveCursor(5 + FRAME_WIDTH - 1, i); cout << "|";
    }
    moveCursor(5, 1); cout << "+";
    moveCursor(5 + FRAME_WIDTH - 1, 1); cout << "+";
    moveCursor(5, FRAME_HEIGHT); cout << "+";
    moveCursor(5 + FRAME_WIDTH - 1, FRAME_HEIGHT); cout << "+";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Dibuja el marco del los mensajes que se le muestran al usuario
void showMessageBox(const string& message) {
    int boxWidth = 60, boxHeight = 7;
    int x = 15;
    int y = 12;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    for (int i = 0; i < boxWidth; ++i) {
        moveCursor(x + i, y); cout << "-";
        moveCursor(x + i, y + boxHeight - 1); cout << "-";
    }
    for (int i = 0; i < boxHeight; ++i) {
        moveCursor(x, y + i); cout << "|";
        moveCursor(x + boxWidth - 1, y + i); cout << "|";
    }
    moveCursor(x, y); cout << "+";
    moveCursor(x + boxWidth - 1, y); cout << "+";
    moveCursor(x, y + boxHeight - 1); cout << "+";
    moveCursor(x + boxWidth - 1, y + boxHeight - 1); cout << "+";

    // Mensaje dentro del cuadro
    moveCursor(x + 2, y + 2);
    cout << message;

    moveCursor(x + 2, y + 4);
    cout << "Presiona una tecla para continuar...";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    _getch();

    // Limpiar cuadro
    for (int i = 0; i < boxHeight; ++i) {
        moveCursor(x, y + i);
        for (int j = 0; j < boxWidth; ++j) cout << " ";
    }
}

// Muestra arte ASCII del jefe desde archivo
void showBossArt(const string& path, int x, int y) {
    ifstream file(path);
    string line;
    int offsetY = 0;
    while (getline(file, line)) {
        moveCursor(x, y + offsetY);
        cout << line;
        offsetY++;
    }
}

// Función principal del sistema de batalla RPG con jefe
void bossBattleRPG(bool (*minigame)(int, int)) {
    int bossHP = 1;
    int playerHP = 100;
    bool bossDefeated = false;

    consoleSettings(); // Configura consola
    consoleCenter(); // Centra ventana
    system("cls"); // Limpia pantalla
    drawBattleFrame(); // Dibuja marco

    while (bossHP > 0 && playerHP > 0) {
        system("cls");
        drawBattleFrame();

        showBossArt("data/bosses/boss2.txt", 20, 3); // Arte del jefe

        moveCursor(90, 5);  cout << "╔══════════════╗";
        moveCursor(90, 6);  cout << "║  Jefe: ???   ║";
        moveCursor(90, 7);  cout << "║ HP: " << bossHP << "       ║";
        moveCursor(90, 8);  cout << "╚══════════════╝";

        moveCursor(90, 10); cout << "╔══════════════╗";
        moveCursor(90, 11); cout << "║  Tú          ║";
        moveCursor(90, 12); cout << "║ HP: " << playerHP << "     ║";
        moveCursor(90, 13); cout << "╚══════════════╝";

        // Opciones de combate
        int optX = 35;
        int optY = 24;
        int optW = 80;
        int optH = 5;

        // Dibujo del cuadro de opciones
        moveCursor(optX, optY); cout << "╔" << string(optW - 2, '═') << "╗";
        for (int i = 1; i < optH - 1; ++i) {
            moveCursor(optX, optY + i);
            cout << "║" << string(optW - 2, ' ') << "║";
        }
        moveCursor(optX, optY + optH - 1); cout << "╚" << string(optW - 2, '═') << "╝";

        // Opciones del menú
        moveCursor(optX + 3, optY + 1);
        cout << "[1] Atacar (Mini juego)    [2] Defender    [3] Huir";

        moveCursor(optX + 3, optY + 2);
        cout << "Elige una opción: ";

        char opcion = _getch();

        if (opcion == '1') {
            for (int i = 0; i < optH; ++i) {
                moveCursor(optX, optY + i);
                cout << string(optW, ' ');
            }

            // Ejecutar minijuego
            bool won = minigame(15, 15);

            if (won) {
                bossHP = 0;
                bossDefeated = true;
            } else {
                playerHP -= 20;
                showMessageBox("Fallaste el minijuego... el jefe te ha golpeado.");
            }
        } else if (opcion == '2') {
            playerHP += 5;
            if (playerHP > 100) playerHP = 100;
            showMessageBox("Te has defendido y recuperado 5 de vida.");
        } else if (opcion == '3') {
            showMessageBox("¡Has huido de la batalla!");
            return;
        } else {
            showMessageBox("Opción no válida.");
        }

        if (playerHP <= 0) {
            showMessageBox("DERROTA - Has sido derrotado...");
            exit(0);
        }
    }

    if (bossDefeated) {
        showMessageBox("¡VICTORIA! - El jefe ha sido vencido.");
    }
}
