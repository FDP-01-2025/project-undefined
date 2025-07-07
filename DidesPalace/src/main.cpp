#include <iostream>
#include <locale.h>
#include <windows.h>
// Capture letters without waiting for enter
#include <conio.h>
#include "utils/menu.h"
#include "levels/level1.h"
#include "levels/level2.h"
#include "levels/level3.h"
#include "levels/level4.h"
#include "./include/utils/sounds.h"

using namespace std;

int main()
{
    // Allows showing special characters
    SetConsoleOutputCP(CP_UTF8);

    // This code block runs continuously unless ESC is pressed
    playMenuMusic();
    while (true)
    {
        system("cls");
        showMenu();

        char option = _getch();
        // Flag that will allow exiting or not from the game
        // If quitGame is true, exits the game (when ESC is pressed)
        // If quitGame is false, continues in the game
        bool quitGame = false;

        switch (option)
        {
        case '1':
            quitGame = Level1();
            break;
        case '2':
            quitGame = Level2();
            break;
        case '3':
            quitGame = Level3();
            break;
         case '4':
            quitGame = Level4();
            break;    
        // ESC key
        case 27:
            quitGame = true;
            break;
        }

        // If quitGame is true, breaks the loop
        if (quitGame)
        {
            cout << "\nExiting game...\n";
            // Breaks the loop
            break;
        }
    }

    return 0;
}