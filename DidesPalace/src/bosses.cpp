#include <iostream>                     // Standard input/output
#include <fstream>                      // For file reading (ASCII art)
#include <string>                       // String handling
#include <windows.h>                    // Windows console functions
#include <conio.h>                      // For key capture
#include "minigames/2_spotDifference.h" // Included minigame
#include "utils/consoleUtils.h"         // Custom console utilities
#include "../include/bosses.h"          // For boss battle handling
#include <iomanip>                      // To format console output (especially with cout) in a more precise and readable way.
#include "./include/utils/sounds.h"     // For sounds effects
using namespace std;

const int FRAME_WIDTH = 120; // Battle frame width
const int FRAME_HEIGHT = 35; // Battle frame height
int bossHP = 100;            // Changed from 1 to 100
int ronda = 1;               // Round counter
int progress = 0;            // Progress for big boss battles

// ================= Visual Functions ===================

// Draws the main battle area frame
void drawBattleFrame()
{
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();

    int x = (consoleWidth - FRAME_WIDTH) / 2;
    int y = (consoleHeight - FRAME_HEIGHT) / 2;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    // Horizontal edges
    for (int i = 0; i < FRAME_WIDTH; ++i)
    {
        moveCursor(x + i, y); // Top line
        cout << "-";
        moveCursor(x + i, y + FRAME_HEIGHT - 1); // Bottom line
        cout << "-";
    }

    // Vertical borders
    for (int i = 0; i < FRAME_HEIGHT; ++i)
    {
        moveCursor(x, y + i); // Left side
        cout << "|";
        moveCursor(x + FRAME_WIDTH - 1, y + i); // Right side
        cout << "|";
    }

    // Corners
    moveCursor(x, y);
    cout << "+";
    moveCursor(x + FRAME_WIDTH - 1, y);
    cout << "+";
    moveCursor(x, y + FRAME_HEIGHT - 1);
    cout << "+";
    moveCursor(x + FRAME_WIDTH - 1, y + FRAME_HEIGHT - 1);
    cout << "+";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Draws the message box frame shown to the user (right-aligned version)
void showMessageBox(const string &message)
{
    int boxWidth = 45; // Reduced width to not take too much space
    int boxHeight = 7;
    int x = 35; // Right-aligned X position (adjusted for full screen)
    int y = 12; // Same Y position (vertically centered)

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    // Draw message box frame
    for (int i = 0; i < boxWidth; ++i)
    {
        moveCursor(x + i, y);
        cout << "-";
        moveCursor(x + i, y + boxHeight - 1);
        cout << "-";
    }
    for (int i = 0; i < boxHeight; ++i)
    {
        moveCursor(x, y + i);
        cout << "|";
        moveCursor(x + boxWidth - 1, y + i);
        cout << "|";
    }
    moveCursor(x, y);
    cout << "+";
    moveCursor(x + boxWidth - 1, y);
    cout << "+";
    moveCursor(x, y + boxHeight - 1);
    cout << "+";
    moveCursor(x + boxWidth - 1, y + boxHeight - 1);
    cout << "+";

    // Message inside box (in Spanish)
    moveCursor(x + 2, y + 2);
    cout << message;

    moveCursor(x + 2, y + 4);
    cout << "Presiona una tecla para continuar...";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    _getch();

    // Clear box
    for (int i = 0; i < boxHeight; ++i)
    {
        moveCursor(x, y + i);
        for (int j = 0; j < boxWidth; ++j)
            cout << " ";
    }
}

void showMessageBoxMiniGame(const string &message, int color)
{
    int boxWidth = 80;
    int boxHeight = 7;

    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();

    int x = (consoleWidth - boxWidth) / 2;
    int y = (consoleHeight - boxHeight) / 2;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set background color based on the color parameter
    // 1 = green, 2 = red, 3 = default (white background)
    int background;
    if (color == 1)
    {
        background = BACKGROUND_GREEN;
    }
    else if (color == 2)
    {
        background = BACKGROUND_RED;
    }
    else if (color == 3)
    {
        background = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    }

    WORD textColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    SetConsoleTextAttribute(hConsole, background | textColor);

    // Fills the whole box with a background color
    for (int i = 0; i < boxHeight; ++i)
    {
        moveCursor(x, y + i);
        for (int j = 0; j < boxWidth; ++j)
            cout << " ";
    }

    for (int i = 0; i < boxWidth; ++i)
    {
        moveCursor(x + i, y);
        cout << "═";
        moveCursor(x + i, y + boxHeight - 1);
        cout << "═";
    }
    for (int i = 0; i < boxHeight; ++i)
    {
        moveCursor(x, y + i);
        cout << "║";
        moveCursor(x + boxWidth - 1, y + i);
        cout << "║";
    }

    // Message centered inside the box
    int messageX = x + (boxWidth - message.length()) / 2;
    int messageY = y + 2;
    moveCursor(messageX, messageY);
    cout << message;
    string prompt = "Presiona una tecla para continuar...";
    int promptX = x + (boxWidth - prompt.length()) / 2;
    int promptY = y + 4;
    moveCursor(promptX, promptY);
    cout << prompt;

    _getch();

    // Restore normal colors (gray on black background)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // Clears the box after pressing the key
    for (int i = 0; i < boxHeight; ++i)
    {
        moveCursor(x, y + i);
        for (int j = 0; j < boxWidth; ++j)
            cout << " ";
    }
}

// Shows ASCII art of the boss from file
void showBossArt(const string &path, int x, int y)
{
    ifstream file(path);
    string line;
    int offsetY = 0;
    while (getline(file, line))
    {
        moveCursor(x, y + offsetY);
        cout << line;
        offsetY++;
    }
}

// Displays a progress bar with color
void drawColoredProgressBar(int x, int y, int progress)
{
    const int barWidth = 20;
    int filled = (progress * barWidth) / 100;

    // Determines the color of progress
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color;
    if (progress <= 30)
        color = FOREGROUND_RED | FOREGROUND_INTENSITY;
    else if (progress <= 70)
        color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    else
        color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

    moveCursor(x, y + 1);
    cout << "Progreso: [";

    // Colored progress bar
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < filled)
            cout << "█";
        else
            cout << "░";
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset color

    cout << "] " << progress << "%";
}

// Main function for the RPG boss battle system
void bossBattleRPG(bool (*minigame)(int, int))
{ 
    bossHP = 100;
    int playerHP = 100;
    bool bossDefeated = false;

    consoleSettings(); // Configure console
    consoleCenter();   // Center window
    system("cls");     // Clear screen
    drawBattleFrame(); // Draw frame

    while (bossHP > 0 && playerHP > 0)
    {
        playBossMusic();
        system("cls");
        drawBattleFrame();

        showBossArt("data/bosses/boss2.txt", 25, 4); // Boss art

        // UI in Spanish
        int x = 90;
        int y = 5;

        moveCursor(x, y);     cout << "╔════════════════╗";
        moveCursor(x, y + 1); cout << "║ -> Jefe:       ║";
        moveCursor(x, y + 2); cout << "║  HP: " << setw(3) << setfill(' ') << bossHP << "       ║";
        moveCursor(x, y + 3); cout << "╚════════════════╝";

        moveCursor(x, y + 5); cout << "╔════════════════╗";
        moveCursor(x, y + 6); cout << "║ ♥ Tú           ║";
        moveCursor(x, y + 7); cout << "║ HP: " << setw(3) << setfill(' ') << playerHP << "        ║";
        moveCursor(x, y + 8); cout << "╚════════════════╝";

        drawColoredProgressBar(40, 5, progress);

        // Combat options
        int optX = 35;
        int optY = 24;
        int optW = 80;
        int optH = 5;

        // Draw options box
        moveCursor(optX, optY);
        cout << "╔" << string(optW - 2, '═') << "╗";
        for (int i = 1; i < optH - 1; ++i)
        {
            moveCursor(optX, optY + i);
            cout << "║" << string(optW - 2, ' ') << "║";
        }
        moveCursor(optX, optY + optH - 1);
        cout << "╚" << string(optW - 2, '═') << "╝";

        // Menu options in Spanish
        moveCursor(optX + 3, optY + 1);
        cout << "[1] Atacar (Mini juego)    [2] Defender    [3] Huir";

        moveCursor(optX + 3, optY + 2);
        cout << "Elige una opción: ";

        char opcion = _getch();

        if (opcion == '1')
        {
            for (int i = 0; i < optH; ++i)
            {
                moveCursor(optX, optY + i);
                cout << string(optW, ' ');
            }

            // Execute minigame
            bool won = minigame(15, 15);
            
            if (won)
            {
                bossHP -= 25; // Reduce 25 HP instead of instant defeat
                if (bossHP <= 0)
                {
                    bossHP = 0;
                    bossDefeated = true;
                }
                playSuccess();
                showMessageBoxMiniGame("😄 ¡Has acertado el minijuego! El jefe pierde 25 puntos de vida 😄", 1);
                
            }
            else
            {
                playerHP -= 20;
                playError();
                showMessageBoxMiniGame("😭 Fallaste el minijuego... el jefe te ha golpeado 😭", 2);
            }
        }
        else if (opcion == '2')
        {
            playHeal();
            playerHP += 5;
            if (playerHP > 100)
                playerHP = 100;
            showMessageBox("Te has defendido y recuperado 5 de vida.");
        }
        else if (opcion == '3')
        {
            playBossGameOver();
            showMessageBox("¡Has huido de la batalla!");
            return;
        }
        else
        {
            playError();
            showMessageBox("Opción no válida.");
        }

        if (playerHP <= 0)
        {
            playBossGameOver();
            showMessageBoxMiniGame("GAME OVER - Has sido derrotado...", 2);
            exit(0);
        }
    }

    if (bossDefeated)
    {
        playLvlPass();
        showMessageBoxMiniGame("🥳¡VICTORIA! - El jefe del nivel ha sido vencido.🥳", 1);
        progress += 25;      // Increment progress for big boss battles
        bossHP = 100;        // Reset boss HP for next battle
        if (progress >= 100) // Check if the progress reaches 100%
        {
            showMessageBoxMiniGame("🥳🤩¡Felicidades! Has derrotado a todos los jefes del juego", 3);
            exit(0); // Exit the game after defeating all bosses
        }
    }
}