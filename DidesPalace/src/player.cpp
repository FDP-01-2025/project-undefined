//Se incluye el archivo de cabecera que define la funcion de player.h
#include "player.h"

//Funcion que mueve al jugador dentro del laberinto
void movePlayer(Maze &maze, char direction)
{
    //Se declaran variables para calcular la nueva posicion del jugador.
    int newX = maze.playerX;
    int newY = maze.playerY;

    //Se evalua la tecla presionada
    switch (direction)
    {
    //Up
    case 'w': 
        newY--;
        break;
    //Down    
    case 's':
        newY++;
        break;
    //Left    
    case 'a':
        newX--;
        break;
    //Right  
    case 'd':
        newX++;
        break;
    default:
        break;
    }

    //Se verifica que la posición está dentro del rango del laberinto
    //y que no es una pared (#)
    if (newX >= 0 && newX < maze.cols &&
        newY >= 0 && newY < maze.rows &&
        maze.grid[newY][newX] != '#')
    {
        // Limpia la posición actual
        maze.grid[maze.playerY][maze.playerX] = '.';

        // Actualiza coordenadas del jugador
        maze.playerX = newX;
        maze.playerY = newY;
    }
}