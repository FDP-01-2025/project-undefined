#include <iostream> // Standard input/output
#include <fstream> // For file reading (ASCII art)
#include <string> // String handling
#include <windows.h> // Windows console functions
#include <conio.h> // For key capture
#include "minigames/2_spotDifference.h" // Included minigame
#include "utils/consoleUtils.h" // Custom console utilities
using namespace std;

const int FRAME_WIDTH = 120; // Battle frame width
const int FRAME_HEIGHT = 35; // Battle frame height

// ================= Visual Functions ===================

// Draws the main battle area frame
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

// Draws the message box frame shown to the user (right-aligned version)
void showMessageBox(const string& message) {
    int boxWidth = 45;  // Reduced width to not take too much space
    int boxHeight = 7;
    int x = 35;         // Right-aligned X position (adjusted for full screen)
    int y = 12;         // Same Y position (vertically centered)

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    // Draw message box frame
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

    // Message inside box (in Spanish)
    moveCursor(x + 2, y + 2);
    cout << message;

    moveCursor(x + 2, y + 4);
    cout << "Presiona una tecla para continuar...";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    _getch();

    // Clear box
    for (int i = 0; i < boxHeight; ++i) {
        moveCursor(x, y + i);
        for (int j = 0; j < boxWidth; ++j) cout << " ";
    }
}

void showMessageBoxMiniGame(const string& message) {
    int boxWidth = 66;
    int boxHeight = 7;
    int x = 50;
    int y = 6;     

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

    moveCursor(x + 2, y + 2);
    cout << message;
    moveCursor(x + 2, y + 4);
    cout << "Presiona una tecla para continuar...";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    _getch();

    for (int i = 0; i < boxHeight; ++i) {
        moveCursor(x, y + i);
        for (int j = 0; j < boxWidth; ++j) cout << " ";
    }
}

// Shows ASCII art of the boss from file
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

// Main function for the RPG boss battle system
void bossBattleRPG(bool (*minigame)(int, int)) {
    int bossHP = 100;  // Changed from 1 to 100
    int playerHP = 100;
    bool bossDefeated = false;

    consoleSettings(); // Configure console
    consoleCenter(); // Center window
    system("cls"); // Clear screen
    drawBattleFrame(); // Draw frame

    while (bossHP > 0 && playerHP > 0) {
        system("cls");
        drawBattleFrame();

        showBossArt("data/bosses/boss2.txt", 20, 3); // Boss art

        // UI in Spanish
        moveCursor(90, 5);  cout << "╔══════════════╗";
        moveCursor(90, 6);  cout << "║  Jefe: ???   ║";
        moveCursor(90, 7);  cout << "║ HP: " << bossHP << "      ║";
        moveCursor(90, 8);  cout << "╚══════════════╝";

        moveCursor(90, 10); cout << "╔══════════════╗";
        moveCursor(90, 11); cout << "║  Tú          ║";
        moveCursor(90, 12); cout << "║ HP: " << playerHP << "      ║";
        moveCursor(90, 13); cout << "╚══════════════╝";

        // Combat options
        int optX = 35;
        int optY = 24;
        int optW = 80;
        int optH = 5;

        // Draw options box
        moveCursor(optX, optY); cout << "╔" << string(optW - 2, '═') << "╗";
        for (int i = 1; i < optH - 1; ++i) {
            moveCursor(optX, optY + i);
            cout << "║" << string(optW - 2, ' ') << "║";
        }
        moveCursor(optX, optY + optH - 1); cout << "╚" << string(optW - 2, '═') << "╝";

        // Menu options in Spanish
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

            // Execute minigame
            bool won = minigame(15, 15);

            if (won) {
                bossHP -= 25;  // Reduce 25 HP instead of instant defeat
                if (bossHP <= 0) {
                    bossHP = 0;
                    bossDefeated = true;
                }
                showMessageBoxMiniGame("¡Has acertado el minijuego! El jefe pierde 25 puntos de vida.");
            } else {
                playerHP -= 20;
                showMessageBoxMiniGame("Fallaste el minijuego... el jefe te ha golpeado.");
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