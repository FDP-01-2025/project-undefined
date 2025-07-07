#include <windows.h>
#include <string>
#include <iostream>
#include <utils/consoleUtils.h>
#include "utils/sounds.h"

// Function to move the cursor
void moveCursor(int x, int y)
{
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to configure the console
void consoleSettings()
{
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_SHOWDEFAULT);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {static_cast<SHORT>(WINDOW_WIDHT), static_cast<SHORT>(WINDOW_HEIGHT)};
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT ventana = {0, 0, static_cast<SHORT>(WINDOW_WIDHT - 1), static_cast<SHORT>(WINDOW_HEIGHT - 1)};
    SetConsoleWindowInfo(hOut, TRUE, &ventana);
}

// Function to center the window
void consoleCenter()
{
    HWND hwnd = GetConsoleWindow();
    if (!hwnd)
        return;

    RECT screen;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &screen, 0);
    int screenWidht = screen.right - screen.left;
    int screenHeight = screen.bottom - screen.top;

    RECT rect;
    GetWindowRect(hwnd, &rect);
    int windowWidht = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    int posX = (screenWidht - windowWidht) / 2;
    int posY = (screenHeight - windowHeight) / 2;

    MoveWindow(hwnd, posX, posY, windowWidht, windowHeight, TRUE);
}

// Changes the text color in the console
void setColor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Gets the console width
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Gets the console height
int getConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

/// Displays a centered message with typewriter-like animation (multi-line support)
void showAnimatedMessage(const std::string &message, int delay, int waitAfter)
{   
    playTypewritter();
    // Clear screen
    system("cls"); 

    // Console size
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();

    // Count how many lines there are (\n).
    int lineCount = 1;
    for (int i = 0; i < message.length(); ++i)
    {
        if (message[i] == '\n')
            ++lineCount;
    }

    // Calculate the vertical position to center all lines
    int yStart = (consoleHeight - lineCount) / 2;

    // Displays each line one by one
    int i = 0;
    int currentLine = 0;
    while (i < message.length())
    {
        // Extract line manually (\n or end)
        std::string line = "";
        while (i < message.length() && message[i] != '\n')
        {
            line += message[i];
            ++i;
        }
        ++i; // break'\n'

        // Calculate horizontal centered position
        int realLength = 0;
        for (int j = 0; j < line.length(); ++j)
            realLength += (line[j] < 0 || line[j] > 127) ? 2 : 1;
        int x = (consoleWidth - realLength) / 2;

        // Show line with animation
        setColor(14);
        moveCursor(x, yStart + currentLine);
        for (int j = 0; j < line.length(); ++j)
        {
            std::cout << line[j] << std::flush;
            Sleep(delay);
        }

        ++currentLine;
    }

    Sleep(waitAfter);

    // Delete displayed lines
    currentLine = 0;
    i = 0;
    while (i < message.length())
    {
        std::string line = "";
        while (i < message.length() && message[i] != '\n')
        {
            line += message[i];
            ++i;
        }
        ++i;

        // Delete with spaces
        int realLength = 0;
        for (int j = 0; j < line.length(); ++j)
            realLength += (line[j] < 0 || line[j] > 127) ? 2 : 1;
        int x = (consoleWidth - realLength) / 2;

        moveCursor(x, yStart + currentLine);
        for (int j = 0; j < realLength; ++j)
            std::cout << " ";

        ++currentLine;
    }

    Sleep(300);
}