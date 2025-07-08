#include "maze.h"
#include <fstream>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <utils/consoleUtils.h>
#include <utils/menu.h>
using namespace std;

// Variables for centering
int marginX = 0;
int marginY = 0;

// Function that loads the maze from a text file using fstream
void loadMazeFromFile(Maze &maze, const char *filePath)
{
    // Open the text file containing the maze
    ifstream file(filePath);

    // Validate the file opened correctly
    if (!file)
    {
        cout << "Error al abrir el archivo: \n"
             << filePath;
        return;
    }

    // Temporary buffer to read each file line
    string line;

    // Initialize variables
    maze.rows = 0;
    maze.cols = 0;

    // Read each file line and store in grid matrix
    while (getline(file, line) && maze.rows < MAX_ROWS)
    {
        // Limit line length to maximum allowed
        if (line.length() > MAX_COLS)
            line = line.substr(0, MAX_COLS);

        // Copy line to maze matrix
        strcpy(maze.grid[maze.rows], line.c_str());

        // Record maze width just once (all rows should have same width)
        if (maze.cols == 0)
            maze.cols = line.length();

        // Find player (P) and boss (B)
        // Scan each character to locate P and B positions
        for (int col = 0; col < maze.cols; ++col)
        {
            if (line[col] == 'P')
            {
                maze.playerX = col;
                maze.playerY = maze.rows;
            }
            else if (line[col] == 'B') // position of the boss//
            {
                maze.bossX = col;
                maze.bossY = maze.rows;
            }
        }

        ++maze.rows;
    }

    // Close the file
    file.close();

    // Calculate margins for centering
    marginX = (WINDOW_WIDHT - maze.cols - 25) / 2;
    marginY = (WINDOW_HEIGHT - maze.rows) / 2;
}

// Function that checks if cell (x,y) is a wall #
bool isWall(const Maze &maze, int y, int x)
{
    return x >= 0 && x < maze.cols && y >= 0 && y < maze.rows && maze.grid[y][x] == '#';
}

// Function to determine wall type (visual)
char typeWall(const Maze &maze, int y, int x)
{
    // If not a wall returns space
    if (!isWall(maze, y, x))
        return ' ';

    // Check if adjacent cells (up, down, left, right) are also walls
    bool up = isWall(maze, y - 1, x);
    bool down = isWall(maze, y + 1, x);
    bool left = isWall(maze, y, x - 1);
    bool right = isWall(maze, y, x + 1);

    // Determine which symbol to draw
    if (up || down)
        return '|';
    if (left || right)
        return '-';
    return '#';
}

// Function to draw the maze
void drawMaze(const Maze &maze, int wallColor)
{
    // Enable color changes in console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    // Draw the maze
    for (int y = 0; y < maze.rows; ++y)
    {
        coord.X = marginX;
        coord.Y = marginY + y;
        SetConsoleCursorPosition(hConsole, coord);

        for (int x = 0; x < maze.cols; ++x)
        {
            // Get current maze cell character (x,y)
            char c = maze.grid[y][x];

            // VISUALIZATION LOGIC
            // Check if it's the player's cell
            if (x == maze.playerX && y == maze.playerY)
            {
                SetConsoleTextAttribute(hConsole, COLOR_PLAYER);
                cout << "♡";
            }
            else if (c == '#')
            {
                SetConsoleTextAttribute(hConsole, wallColor);
                // Draw '|' or '-' depending on shape (isWall function)
                cout << typeWall(maze, y, x);
            }
            else if (c == 'B')
            {
                SetConsoleTextAttribute(hConsole, COLOR_BOSS);
                cout << 'B';
            }
            else
            {
                SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
                cout << c;
            }
        }

        // Draw instructions next to the maze
        coord.X = marginX + maze.cols + 2;
        SetConsoleCursorPosition(hConsole, coord);
        SetConsoleTextAttribute(hConsole, COLOR_STATS);

        // Show instructions beside the maze
        switch (y)
        {
        case 0:
            cout << "=== Estado del jugador ===";
            break;
        case 2:
            cout << "Pos: (" << maze.playerX << "," << maze.playerY << ")";
            break;
        case 4:
            cout << "Controles:";
            break;
        case 5:
            cout << "W = arriba";
            break;
        case 6:
            cout << "S = abajo";
            break;
        case 7:
            cout << "A = izquierda";
            break;
        case 8:
            cout << "D = derecha";
            break;
        case 10:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Q = salir del juego";
            break;
        default:
            cout << " ";
            break;
        }
    }

    // Restore default colors
    SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
}

// Function that only updates the player position in the console
void updatePlayerPosition(const Maze &maze, int oldX, int oldY)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Erase the previous position
    moveCursor(marginX + oldX, marginY + oldY);
    SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
    cout << '.';

    // Draw player in the new position
    moveCursor(marginX + maze.playerX, marginY + maze.playerY);
    SetConsoleTextAttribute(hConsole, COLOR_PLAYER);
    cout << "♡";

    // Reset color
    SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
}


// Function that updates the player's position in the right-side panel
void updatePlayerStats(const Maze &maze)
{
    // Get console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    // Set cursor to the coordinates where the position text is displayed
    coord.X = marginX + maze.cols + 2;
    coord.Y = marginY + 2;

    // Move the cursor to the desired position
    SetConsoleCursorPosition(hConsole, coord);

    // Set the text color to the stats color
    SetConsoleTextAttribute(hConsole, COLOR_STATS);

    // Display updated player coordinates
    cout << "Pos: (" << maze.playerX << "," << maze.playerY << ")  ";
}