#include "utils/menu.h"
#include "utils/consoleUtils.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void drawBackground()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Get the console size
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();

    for (int y = 0; y < consoleHeight; ++y)
    {
        for (int x = 0; x < consoleWidth; ++x)
        {
            moveCursor(x, y);

            if ((x + y) % 17 == 0)
            {
                // Light yellow stars (#fff3b0)
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "*";
            }
            else if (x == 0 || x == consoleWidth - 1)
            {
                // Dark blue vertical walls
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                cout << "|";
            }
            else if (y == 0 || y == consoleHeight - 1)
            {
                // Dark blue horizontal walls
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                cout << "-";
            }
            else
            {
                cout << " ";
            }
        }
    }
}

void showMenu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    drawBackground();

    // Text in yellow color
    setColor(6);

    string titleArt[] = {
        "██████╗░██╗░█████╗░███████╗██╗░██████╗  ██████╗░░█████╗░██╗░░░░░░█████╗░░█████╗░███████╗",
        "██╔══██╗██║██╔══██╗██╔════╝╚█║██╔════╝  ██╔══██╗██╔══██╗██║░░░░░██╔══██╗██╔══██╗██╔════╝",
        "██║░░██║██║██║░░╚═╝█████╗░░░╚╝╚█████╗░  ██████╔╝███████║██║░░░░░███████║██║░░╚═╝█████╗░░",
        "██║░░██║██║██║░░██╗██╔══╝░░░░░░╚═══██╗  ██╔═══╝░██╔══██║██║░░░░░██╔══██║██║░░██╗██╔══╝░░",
        "██████╔╝██║╚█████╔╝███████╗░░░██████╔╝  ██║░░░░░██║░░██║███████╗██║░░██║╚█████╔╝███████╗",
        "╚═════╝░╚═╝░╚════╝░╚══════╝░░░╚═════╝░  ╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝░╚════╝░╚══════╝",
        "                                    DICE'S PALACE                                       "};

    // Approximate width and height of the menu box.
    int boxWidth = 85;
    int boxHeight = 13;

    // Get actual console size
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();

    // Centered coordinates
    int x = (consoleWidth - boxWidth) / 2;
    int y = (consoleHeight - boxHeight) / 2;

    // Options
    string opt1 = "1. Empezar";
    string opt2 = "2. Nivel 2";
    string opt3 = "3. Nivel 3";
    string opt4 = "4. Nivel 4";
    string opt5 = "ESC. Salir del juego";
    string prompt = "";

    int currentY = y;

    // Show centered title
    for (const string &line : titleArt)
    {
        moveCursor(x, currentY++);
        cout << line;
    }

    // space after the title
    currentY++; 

    // Show centered options
    moveCursor(x + (boxWidth - opt1.size()) / 2, currentY++);
    cout << opt1;

    moveCursor(x + (boxWidth - opt2.size()) / 2, currentY++);
    cout << opt2;

    moveCursor(x + (boxWidth - opt3.size()) / 2, currentY++);
    cout << opt3;

    moveCursor(x + (boxWidth - opt4.size()) / 2, currentY++);
    cout << opt4;

    moveCursor(x + (boxWidth - opt5.size()) / 2, currentY + 2);
    setColor(12); // Bright red color for the exit option
    cout << opt5;

    moveCursor(x + (boxWidth - prompt.size()) / 2, currentY++);
    cout << prompt;

    // Restore normal color
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
