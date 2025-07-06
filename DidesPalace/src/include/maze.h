#ifndef MAZE_H
#define MAZE_H

// Definition of maximum maze sizes
#define MAX_ROWS 70 // Rows
#define MAX_COLS 70 // Columns

#include <windows.h>

// Structure that stores the maze content
struct Maze
{
    // Maze matrix
    char grid[MAX_ROWS][MAX_COLS];
    // Actual size of the loaded maze (from txt file)
    int rows, cols;
    // Player position (P)
    int playerX, playerY;
    // Boss position (B)
    int bossX, bossY;
};

// FUNCTIONS (Will be implemented in maze.cpp)
void loadMazeFromFile(Maze &maze, const char *filePath);
void drawMaze(const Maze &maze, int wallColor);
bool isWall(const Maze &maze, int y, int x);
char typeWall(const Maze &maze, int y, int x);
void updatePlayerPosition(const Maze &maze, int oldX, int oldY);
void updatePlayerStats(const Maze &maze);

#endif