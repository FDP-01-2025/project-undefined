#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "maze.h"
#include "player.h"
#include "bosses.h"
#include "levels/level2.h"
#include "./minigames/2_spotDifference.h"
using namespace std;

bool Level2()
{
    // Hide cursor
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    
    // Clear screen completely when entering the level
    system("cls");
    
    // Create a Maze instance
    Maze maze;

    // Load the maze (Parameters: Maze instance and file path)
    loadMazeFromFile(maze, "data/levels/level2_map.txt");

    cout << "==== LEVEL 2 =====";
    // Draw initial maze
    // Parameters: Maze instance and wall color
    drawMaze(maze, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // This code block runs continuously unless 'q' or ESC is pressed
    while (true)
    {
        // Capture the key pressed by the user
        char key = _getch();
        
        // If 'q' is pressed, return to main menu
        if (key == 'q' || key == 'Q'){
            return false;
        // If ESC is pressed, end the game
        } else if (key == 27){
            // Return true to indicate game exit
            return true;
        }
            
        // Function that handles movement (Parameters: Maze instance and captured key)
        if (movePlayer(maze, key)) {
            // Only redraw if movement was valid
            drawMaze(maze, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            if (maze.grid[maze.playerY][maze.playerX] == 'B') {
                bossBattleRPG(playSpotDifference);
                return false; // If player survives, level ends
            }
        }
        
        // Small pause 
        Sleep(16);  
    }
}