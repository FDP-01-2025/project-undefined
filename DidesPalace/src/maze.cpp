#include "maze.h"
#include <fstream>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <utils/consoleUtils.h>
#include <utils/menu.h>
using namespace std;

// Variables para centrado
int marginX = 0;
int marginY = 0;

// Función que carga el laberinto del archivo de texto usando fstream
void loadMazeFromFile(Maze &maze, const char *filePath)
{
    // Se abre el archivo de texto que contiene el laberinto
    ifstream file(filePath);

    // Se valida que el archivo se abrió correctamente
    if (!file)
    {
        cout << "Error al abrir el archivo: \n"
             << filePath;
        return;
    }

    // Buffer temporal para leer cada línea del archivo.
    string line;

    // Se inicializan las variables
    maze.rows = 0;
    maze.cols = 0;

    // Se lee cada línea del archivo y se guarda en la matriz grid
    while (getline(file, line) && maze.rows < MAX_ROWS)
    {
        // Limita la longitud de la línea al máximo permitido
        if (line.length() > MAX_COLS)
            line = line.substr(0, MAX_COLS);

        // Copia la línea a la matriz del laberinto
        strcpy(maze.grid[maze.rows], line.c_str());

        // Registra el ancho del laberinto solo una vez (todas las filas deben tener el mismo)
        if (maze.cols == 0)
            maze.cols = line.length();

        // Busca jugador (P) y jefe (B)
        // Se recorre cada caracter para encontrar la posicion de P y B
        for (int col = 0; col < maze.cols; ++col)
        {
            if (line[col] == 'P')
            {
                maze.playerX = col;
                maze.playerY = maze.rows;
            }
            else if (line[col] == 'B')
            {
                maze.bossX = col;
                maze.bossY = maze.rows;
            }
        }

        ++maze.rows;
    }

    // Se cierra el archivo
    file.close();

    // Calcular márgenes para centrado
    marginX = (WINDOW_WIDHT - maze.cols - 25) / 2;
    marginY = (WINDOW_HEIGHT - maze.rows) / 2;
}

// Funcion que verifica si la celda (x,y) es una pared #.
bool isWall(const Maze &maze, int y, int x)
{
    return x >= 0 && x < maze.cols && y >= 0 && y < maze.rows && maze.grid[y][x] == '#';
}

// Funcion para determinar el tipo de pared (visual)
char typeWall(const Maze &maze, int y, int x)
{
    // Si no es pared devuelve un espacio.
    if (!isWall(maze, y, x))
        return ' ';

    // Se verifica si las celdas(Arriba, abajo, derecha, izquierda) tambien son paredes
    bool up = isWall(maze, y - 1, x);
    bool down = isWall(maze, y + 1, x);
    bool left = isWall(maze, y, x - 1);
    bool right = isWall(maze, y, x + 1);

    // Se decide el simbolo a dibujar
    if (up || down)
        return '|';
    if (left || right)
        return '-';
    return '#';
}

// Función para dibujar el laberinto
void drawMaze(const Maze &maze, WORD wallColor)
{
    // Permite el cambio de colores en la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    // Dibuja el laberinto
    for (int y = 0; y < maze.rows; ++y)
    {
        coord.X = marginX;
        coord.Y = marginY + y;
        SetConsoleCursorPosition(hConsole, coord);

        for (int x = 0; x < maze.cols; ++x)
        {
            // Obtiene el caracter actual del laberinto (x,y)
            char c = maze.grid[y][x];

            // LOGICA DE VISUALIZACION
            // Verifica si es la celda donde esta el jugador
            if (x == maze.playerX && y == maze.playerY)
            {
                SetConsoleTextAttribute(hConsole, COLOR_PLAYER);
                cout << "♡";
            }
            else if (c == '#')
            {
                SetConsoleTextAttribute(hConsole, wallColor);
                // Dibuja '|' o '-', esto depende de la forma (Funcion isWallet)
                cout << typeWall(maze, y, x);
            }
            else if (c == 'B')
            {
                SetConsoleTextAttribute(hConsole, COLOR_BOSS);
                cout << 'B';
            }
            else
            {
                SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
                cout << c;
            }
        }

        // Dibuja las instrucciones que salen a la par del laberinto
        coord.X = marginX + maze.cols + 2;
        SetConsoleCursorPosition(hConsole, coord);
        SetConsoleTextAttribute(hConsole, COLOR_STATS);

        // Se muestran las instrucciones del lado del laberinto
        switch (y)
        {
        case 0:
            cout << "=== Estado del jugador ===";
            break;
        case 2:
            cout << "Pos: (" << maze.playerX << "," << maze.playerY << ")";
            break;
        case 4:
            cout << "Controles:";
            break;
        case 5:
            cout << "W = arriba";
            break;
        case 6:
            cout << "S = abajo";
            break;
        case 7:
            cout << "A = izquierda";
            break;
        case 8:
            cout << "D = derecha";
            break;
        case 10:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "Q = salir del juego";
            break;
        default:
            cout << " ";
            break;
        }
    }

    // Restaura a los colores originales
    SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
}