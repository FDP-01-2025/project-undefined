#include "player.h"
#include "maze.h"

// Function that moves the player within the maze
// Returns true if the movement was valid and executed
bool movePlayer(Maze &maze, char direction) {
    // Variables to calculate the player's new position
    int newX = maze.playerX;
    int newY = maze.playerY;

    // Evaluate pressed key
    switch (direction) {
    // Up
    case 'w': case 'W':
        newY--;
        break;
    // Down    
    case 's': case 'S':
        newY++;
        break;
    // Left    
    case 'a': case 'A':
        newX--;
        break;
    // Right  
    case 'd': case 'D':
        newX++;
        break;
    default:
        return false; // Invalid key
    }

    // Verify the position is within maze boundaries
    // and not a wall (#)
    if (!isWall(maze, newY, newX)) 
    {
        // Clears current position
        maze.grid[maze.playerY][maze.playerX] = '.';

        // Updates player coordinates
        maze.playerX = newX;
        maze.playerY = newY;
        
        return true; // Valid movement
    }
    return false; // Invalid movement
}