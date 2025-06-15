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
        
   //Se ejecuta este bloque de codigo siempre, a menos que se presione q.
    while(true){
        //Se limpia la consola
        system("cls");

        //Dibuja el laberinto en consola (Parametros: Instancia de maze)
        drawMaze(&maze);

        cout << "\nUsa W/A/S/D para moverte. Q para salir.\n";
        
        //Se muestran las posiciones del jugador
        cout << "\nPosicion inicial del jugador: (" << maze.playerX << ", " << maze.playerY << ")" << endl;

        //Captura la letra que presiono el usuario
        char key = _getch();
        //Si la letra presionada es q se termina el programa.
        if (key == 'q') break;
        
        //Funcion que permite el movimiento (Parametros que recibe: Instancia de maze y la letra capturada)
        movePlayer(&maze, key);

    }
    return 0;
}