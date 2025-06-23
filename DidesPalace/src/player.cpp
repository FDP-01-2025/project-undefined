#include "player.h"
#include "maze.h"

// Función que mueve al jugador dentro del laberinto
// Devuelve true si el movimiento fue válido y se realizó
bool movePlayer(Maze &maze, char direction) {
    // Se declaran variables para calcular la nueva posicion del jugador.
    int newX = maze.playerX;
    int newY = maze.playerY;

    // Se evalua la tecla presionada
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
        return false; // Tecla no válida
    }

    // Se verifica que la posición está dentro del rango del laberinto
    // y que no es una pared (#)
    if (!isWall(maze, newY, newX)) 
    {
        // Limpia la posición actual
        maze.grid[maze.playerY][maze.playerX] = '.';

        // Actualiza coordenadas del jugador
        maze.playerX = newX;
        maze.playerY = newY;
        
        return true; // Movimiento válido
    }
    return false; // Movimiento no válido
}