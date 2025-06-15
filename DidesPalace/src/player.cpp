#include "player.h"

void movePlayer(Maze *maze, char direction)
{
    int newX = maze->playerX;
    int newY = maze->playerY;

    switch (direction)
    {
    case 'w':
        newY--;
        break;
    case 's':
        newY++;
        break;
    case 'a':
        newX--;
        break;
    case 'd':
        newX++;
        break;
    default:
        break;
    }

    if (newX >= 0 && newX < maze->cols &&
        newY >= 0 && newY < maze->rows &&
        maze->grid[newY][newX] != '#')
    {
        // Limpia la posición actual
        maze->grid[maze->playerY][maze->playerX] = '.';

        // Actualiza coordenadas del jugador
        maze->playerX = newX;
        maze->playerY = newY;
    }
}