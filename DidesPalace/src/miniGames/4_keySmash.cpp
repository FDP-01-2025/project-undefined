#include "minigames/4_keySmash.h"
#include <iostream>
#include <windows.h>
#include "conio.h" // Library for keyboard input handling
#include <ctime>   // For random number generation
#include <cstdlib>
#include "../include/utils/consoleUtils.h"
#include "../include/bosses.h" // For boss battle handling
#include "../include/utils/sounds.h"

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

    // Draws the horizontal borders
    for (int i = 0; i <= WIDTH; i++)
    {
        moveCursor(PosX + i, PosY);
        cout << "#";
        moveCursor(PosX + i, PosY + HEIGHT + 1);
        cout << "#";
    }

    // Draws the vertical borders
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

    // Calculate coordinates to center the game frame
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startX = (consoleWidth - WIDTH) / 2;
    int startY = (consoleHeight - HEIGHT) / 2 - 1;

    while (bossHP > 0)
    {
        int numKeys = 4 + ronda - 1;
        int scoreToWin = 30 + (ronda - 1) * 10; // Score needed to win the round
        // Initialize starting speed
        int speed = 350 - (ronda - 1) * 40; // Speed decreases as rounds increase
        if (speed < 80)
        {
            speed = 80; // Minimum speed limit
        }

        // Funcion to show an animated message (Title of the game)
        showAnimatedMessage("<<<< SMASH KEY - RONDA " + to_string(ronda) + " >>>>" 
        + "\nPresiona las teclas correctas antes de que lleguen al final" 
        + "\n\n➣ Letras: " + to_string(numKeys) 
        + "\n➣ Velocidad: " + to_string(speed) + " ms" + 
        + "\n➣ Objetivo: Llega a " + to_string(scoreToWin) + " puntos para ganar la ronda");
        
        playBossMusic();
        // Draws the frame one pixel before to enclose the game area
        drawFrame(startX - 1, startY - 1);

        moveCursor(startX, startY - 6);
        setColor(6);
        cout << "    <<<<< 𝑺𝒎𝒂𝒔𝒉 𝒌𝒆𝒚 - " << "𝑹𝒐𝒏𝒅𝒂: " << ronda << " >>>>>";
        setColor(15);
        moveCursor(startX, startY - 4);
        cout << "• Cantidad de letras: " << numKeys;
        moveCursor(startX, startY - 3);
        cout << "• Velocidad: " << speed << " ms";

        // GAME LOGIC
        Key *keys = new Key[numKeys];

        // Initialize score
        int score = 0;

        // Initialize timer
        DWORD lastSpeedUp = GetTickCount();

        // Initialize letters at random positions within the game area
        for (int i = 0; i < numKeys; i++)
        {
            keys[i].letter = getRandomKey();
            keys[i].x = startX + 1 + rand() % (WIDTH - 2);
            keys[i].y = startY;
            keys[i].active = true;
        }

        // Erase previous letter before drawing the new one
        while (true)
        {
            for (int i = 0; i < numKeys; i++)
            {
                if (keys[i].active && keys[i].y > startY)
                {
                    moveCursor(keys[i].x, keys[i].y - 1), cout << " ";
                }
            }

            // Draw new letters
            for (int i = 0; i < numKeys; i++)
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
                for (int i = 0; i < numKeys; i++)
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
            for (int i = 0; i < numKeys; i++)
            {
                if (keys[i].active)
                {
                    keys[i].y++;
                    // If letter reaches bottom of game area, it's considered a failure
                    if (keys[i].y > startY + HEIGHT)
                    {
                        playError();
                        Sleep(2000); // Wait for 2 second before ending the game
                        moveCursor(startX, startY + HEIGHT + 5);
                        system("pause");
                        delete[] keys; // Free memory
                        return false;  // Ends game
                    }
                }
            }

            // Display current score
            moveCursor(startX, startY + HEIGHT + 2);
            setColor(10);
            cout << "✽ Puntaje: " << score << "    ";

            // If score reaches 50, player wins
            if (score >= scoreToWin)
            {
                // Wait for 2 seconds before continuing
                Sleep(2000);
                playSuccess();
                setColor(10);
                moveCursor(startX, startY + HEIGHT + 3);
                cout << "¡Felicidades pasaste la ronda!";
                moveCursor(startX, startY + HEIGHT + 4);
                cout << "Presiona una tecla para continuar...";
                _getch();         // Wait for player to press a key
                ronda++;          // Increase round number
                scoreToWin += 10; // Increase score needed to win next round

                delete[] keys; // Free memory
                return true;   // Ends game
            }

            // Increase game speed every 15 seconds
            if (GetTickCount() - lastSpeedUp >= 5000 && speed > 50)
            {
                speed -= 20;
                lastSpeedUp = GetTickCount();
            }

            Sleep(speed); // Controls game speed
        }
    }
}