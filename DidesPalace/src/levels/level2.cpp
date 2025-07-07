#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "maze.h"
#include "player.h"
#include "bosses.h"
#include "levels/level2.h"
#include "levels/level3.h"
#include <utils/consoleUtils.h>
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
    cout << "\n";
    string title = "========= LEVEL 2 =========\n";
    moveCursor((WINDOW_WIDHT - title.size()) / 2, 0);
    cout << title;
    // Draw initial maze
    // Parameters: Maze instance and wall color
    drawMaze(maze, 5);

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
            updatePlayerStats(maze); // updates only the right side (current position and controls)

            if (maze.grid[maze.playerY][maze.playerX] == 'B') {
                bossBattleRPG(playSpotDifference);
                Level3(); // Proceed to next level after boss battle
                return false; // If player survives, level ends
            }
        }
        
        // Small pause 
        Sleep(16);  
    }
}