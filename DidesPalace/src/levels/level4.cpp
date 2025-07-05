#include <iostream>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "maze.h"
#include "player.h"
#include "bosses.h"
#include "levels/level4.h"
#include <utils/consoleUtils.h>
#include "./minigames/4_keySmash.h"
using namespace std;

bool Level4()
{
    // Ocultar cursor
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // Limpiar pantalla completamente al entrar al nivel
    system("cls");

    // Se crea una instancia de Maze
    Maze maze;

    // Se carga el laberinto (Parametros que recibe: Instancia de Maze y la ruta del archivo)
    loadMazeFromFile(maze, "data/levels/level4_map.txt");

    //Diseño del título
    cout << "\n";
    string title = "========= NIVEL 4 =========\n";
    moveCursor((WINDOW_WIDHT - title.size()) / 2, 0);
    cout << title;

    // Dibujar el laberinto inicial
    // Parametros que se le pasa: Instancia de maze y el color que van a tener las paredes del laberinto
    drawMaze(maze, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    // Se ejecuta este bloque de codigo siempre, a menos que se presione q o esc.
    while (true)
    {
        // Captura la letra que presiono el usuario
        char key = _getch();

        // Si la letra presionada es q regresa al menu principal.
        if (key == 'q' || key == 'Q')
        {
            return false;
            // Si presiona esc se termina el juego
        }
        else if (key == 27)
        {
            // Devuelve true para indicar salida del juego
            return true;
        }

        // Funcion que permite el movimiento (Parametros que recibe: Instancia de maze y la letra capturada)
        if (movePlayer(maze, key))
        {
            // Solo redibujar si hubo movimiento válido
            drawMaze(maze, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

            // Si logra llegar al jefe (B) pasa al mini juego
            if (maze.grid[maze.playerY][maze.playerX] == 'B') // Si llega al jefe
            {
                bossBattleRPG(playKeySmash); // Llama al mini juego de Key Smash
                return false;
            }
        }

        // Pequeña pausa
        Sleep(16);
    }
}