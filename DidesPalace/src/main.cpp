#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "maze.h"
#include "player.h"

using namespace std;

int main () {
        //Se crea una instancia de Maze 
    Maze maze;
    //Permite mostrar caracteres especiales
    SetConsoleOutputCP(CP_UTF8); 

    //Se carga el laberinto (Parametros que recibe: Instancia de Maze y la ruta del archivo)
    loadMazeFromFile(&maze, "data/levels/level1_map.txt");
    cout << "=== Laberinto ===\n";
        
    while(true){
        system("cls");

        //Dibuja el laberinto en consola (Parametros: Instancia de maze)
        drawMaze(&maze);

        cout << "\nUsa W/A/S/D para moverte. Q para salir.\n";
        
        //Se muestran las posiciones del jugador
        cout << "\nPosicion inicial del jugador: (" << maze.playerX << ", " << maze.playerY << ")" << endl;

        char key = _getch();
        if (key == 'q') break;
        
        movePlayer(&maze, key);

    }
    return 0;
}