#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "maze.h"
#include "player.h"
#include "levels/level1.h"
using namespace std;


bool Level1()
{
    // Se crea una instancia de Maze
    Maze maze;

    // Se carga el laberinto (Parametros que recibe: Instancia de Maze y la ruta del archivo)
    loadMazeFromFile(maze, "data/levels/level1_map.txt");

    // Se ejecuta este bloque de codigo siempre, a menos que se presione q o esc.
    while (true)
    {
        // Se limpia la consola
        system("cls");

        // Dibuja el laberinto en consola (Parametros: Instancia de maze)
        cout << "=== NIVEL 1 ===\n";
        drawMaze(maze);

        // Captura la letra que presiono el usuario
        char key = _getch();
        // Si la letra presionada es q regresa al menu principal.
        if (key == 'q'){
            return false;
        //Si presiona esc se termina el juego    
        } else if (key == 27){
            //Devuelve
            return true;
        }
            
        // Funcion que permite el movimiento (Parametros que recibe: Instancia de maze y la letra capturada)
        movePlayer(maze, key);

         // Si logra llegar al jefe (B) pasa al mini juego
        if (maze.grid[maze.playerY][maze.playerX] == 'B') // Si llega al jefe
        {
            cout << "\n¡Nivel completado!\n";
            system("pause");
            return false;
        }
    }
  
}