#include <iostream>
#include "maze.h"
#include <locale.h>

using namespace std;

int main () {
    //Se crea una instancia de Maze 
    Maze maze;
    //Se carga el laberinto (Parametros que recibe: Instancia de Maze y la ruta del archivo)
    loadMazeFromFile(&maze, "data/levels/level1_map.txt");
    cout << "=== Laberinto ===\n";
    
    //Dibuja el laberinto en consola (Parametros: Instancia de maze)
    drawMaze(&maze);

    //Se muestran las posiciones del jugador
    cout << "\nPosicion inicial del jugador: (" << maze.playerX << ", " << maze.playerY << ")" << endl;
         
    //Se muestran las posiciones del jefe.
    cout << "Posicion del jefe: (" << maze.bossX << ", " << maze.bossY << ")" << endl;
    
    return 0;
}