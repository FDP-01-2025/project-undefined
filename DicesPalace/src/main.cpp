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
#include "./include/utils/story.h"

using namespace std;

int main()
{
    // Allows showing special characters
    SetConsoleOutputCP(CP_UTF8);
    while (true)
    {
        // This code block runs continuously unless ESC is pressed
        playMenuMusic();
        system("cls");
        showMenu();

        char option = _getch();
        // Flag that will allow exiting or not from the game
        // If quitGame is true, exits the game (when ESC is pressed)
        // If quitGame is false, continues in the game
        bool quitGame = false;

        switch (option)
        {
        //Enter   
        case 13:
            quitGame = Level1();
            break;
        // Key h    
        case 104:
            quitGame = showStory();
            break;
        // ESC    
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