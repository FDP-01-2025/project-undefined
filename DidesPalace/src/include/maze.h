#ifndef MAZE_H
#define MAZE_H

//Definición de tamaños máximos del laberinto
#define MAX_ROWS 50 //Filas
#define MAX_COLS 50 //Columnas

//Estructura que guarda el contenido del laberinto
struct Maze
{
    // Matriz del laberinto
    char grid[MAX_ROWS][MAX_COLS];
    // Tamaño real del laberinto cargado (Del archivo txt)
    int rows, cols;
    // Posicion del jugador (P)
    int playerX, playerY;
    // Posicion del jefe (B)
    int bossX, bossY;
};

// FUNCIONES (Se implementaran en el maze.cpp)
void loadMazeFromFile(Maze &maze, const char *filePath);
void drawMaze(const Maze &maze);
bool isWall(const Maze &maze, int y, int x);
char typeWall(const Maze &maze, int y, int x);

#endif