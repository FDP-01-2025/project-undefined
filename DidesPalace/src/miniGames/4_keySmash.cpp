#include "minigames/4_keySmash.h"
#include <iostream>
#include <windows.h>
#include "conio.h" // Library for keyboard input handling
#include <ctime>   // For random number generation
#include <cstdlib>
#include "../include/utils/consoleUtils.h"
using namespace std;

// Allows access to Windows console (cursor and color manipulation)
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Generates a random letter between 'A' and 'Z'
char getRandomKey()
{
    return 'A' + rand() % 26;
}

// Draws a frame around the game area
void drawFrame(int PosX, int PosY)
{
    setColor(11);

    // Draws horizontal borders
    for (int i = 0; i <= WIDTH; i++)
    {
        moveCursor(PosX + i, PosY);
        cout << "#";
        moveCursor(PosX + i, PosY + HEIGHT + 1);
        cout << "#";
    }

    // Draws vertical borders
    for (int i = 0; i <= HEIGHT + 1; i++)
    {
        moveCursor(PosX, PosY + i);
        cout << "#";
        moveCursor(PosX + WIDTH, PosY + i);
        cout << "#";
    }
}

bool playKeySmash(int posX, int posY)
{
    // Clear the console
    system("cls");
    // Initialize random numbers
    srand(time(0));

    // Calculate coordinates to center the console frame
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startX = (consoleWidth - WIDTH) / 2;
    int startY = (consoleHeight - HEIGHT) / 2 - 1;

    // Draws the frame one pixel before to enclose the game area
    drawFrame(startX - 1, startY - 1);

    // GAME LOGIC
    // Array of 5 letters that will fall simultaneously
    Key keys[NUM_KEYS];

    // Initialize score
    int score = 0;
    // Initialize starting speed
    int speed = 300;
    // Initialize timer
    DWORD lastSpeedUp = GetTickCount();

    // Initialize letters at random positions within the game area
    for (int i = 0; i < NUM_KEYS; i++)
    {
        keys[i].letter = getRandomKey();
        keys[i].x = startX + 1 + rand() % (WIDTH - 2);
        keys[i].y = startY;
        keys[i].active = true;
    }

    // Erase previous letter before drawing the new one
    while (true)
    {
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].active && keys[i].y > startY)
            {
                moveCursor(keys[i].x, keys[i].y - 1), cout << " ";
            }
        }

        // Draw new letters
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].active)
            {
                moveCursor(keys[i].x, keys[i].y);
                setColor(14);
                cout << keys[i].letter;
            }
        }

        // Capture pressed key
        if (_kbhit())
        {
            char keyPressed = toupper(_getch()); // Captures pressed key and converts to uppercase
            for (int i = 0; i < NUM_KEYS; i++)
            {
                if (keys[i].active && keyPressed == keys[i].letter)
                {
                    moveCursor(keys[i].x, keys[i].y);
                    cout << " "; // Erases the correct letter
                    score++;
                    keys[i].letter = getRandomKey(); // Generates new letter
                    keys[i].x = startX + 1 + rand() % (WIDTH - 2);
                    keys[i].y = startY; // Resets vertical position
                }
            }
        }

        // Move letter downward
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].active)
            {
                keys[i].y++;
                // If letter reaches bottom of game area, it's considered a failure
                if (keys[i].y > startY + HEIGHT)
                {
                    setColor(12);
                    moveCursor(startX, startY + HEIGHT + 3);
                    cout << "¡Fallaste! Puntos: " << score;
                    moveCursor(startX, startY + HEIGHT + 4);
                    cout << "Presiona una tecla para continuar...";
                    _getch();
                    return false; // Ends game
                }
            }
        }

        // Display current score
        moveCursor(startX, startY + HEIGHT + 2);
        setColor(10);
        cout << "Puntaje: " << score << "    ";

        // If score reaches 50, player wins
        if (score >= 50) 
        {
            setColor(10);
            moveCursor(startX, startY + HEIGHT + 3);
            cout << "¡Felicidades! Has ganado con " << score << " puntos.";
            moveCursor(startX, startY + HEIGHT + 4);
            cout << "Presiona una tecla para continuar...";
            _getch();
            return true; // Ends game
        }

        // Increase game speed every 15 seconds
        if (GetTickCount() - lastSpeedUp >= 15000 && speed > 50)
        {
            speed -= 50;
            lastSpeedUp = GetTickCount();
        }

        Sleep(speed); // Controls game speed
    }
}