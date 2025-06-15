#include "maze.h" // 
#include <stdio.h> //Libreria que permite acceder a archivos externos (FILE)
#include <string.h>
#include <iostream>
#include <windows.h>
using namespace std;

//Funcion que carga el laberinto del archivo de texto
void loadMazeFromFile(Maze* maze, const char* filePath){
    //Se abre el archivo de texto que contiene el laberinto
    FILE* file = fopen(filePath, "r");

    //Se valida que el archivo se abrio correctamente
    if(!file){
        cout << "Error al abrir el archivo: \n" <<  filePath;
    }

    //Buffer temporal para leer cada linea del archivo.
    char line[MAX_COLS + 1];
    //Se inicializan las varibales
    maze->rows = 0;
    maze->cols = 0;

    //Se lee cada linea del archivo y se guarda en la matriz grid
    while(fgets(line, sizeof(line), file) && maze->rows < MAX_ROWS){
        //Elimina salto de linea si existe
        line[strcspn(line, "\n")] = '\0';

        //Copia la linea a la matriz
        strcpy(maze->grid[maze->rows], line);
        maze->cols =strlen(line); //Todas las filas deber tener el mismo ancho

        //Buscar el jugador (P) y jefe (B)
        //Se recorre cada caracter para encontrar la posicion de P y B
        for (int col = 0; col < maze->cols; ++col){
            if(line[col] == 'P'){
                maze->playerX = col;
                maze->playerY = maze->rows;
            }else if(line[col] == 'B'){
                maze->bossX = col;
                maze->bossY = maze->rows;
            }
        }
        maze->rows++;
    }
    //Se cierra el archivo
    fclose(file);
}

//Funcion que verifica si la celda (x,y) es una pared #.
bool isWall(const Maze* maze, int y, int x){
    return 
        x >= 0 && x < maze->cols && y >= 0 && y < maze->rows && maze->grid[y][x] == '#';
}

//Funcion que decide que simbolo grafico se usa para una pared
char typeWall(const Maze* maze, int y, int x){
    //Si no es pared devuelve un espacio.
    if (!isWall(maze, y, x)) return ' ';

    //Se verifica si las celdas(Arriba, abajo, derecha, izquierda) tambien son paredes
    bool up = isWall(maze, y -1, x);
    bool down = isWall(maze, y + 1, x);
    bool left = isWall(maze, y, x -1 );
    bool right =  isWall(maze, y, x + 1);

    //Se decide el simbolo a dibujar
    if(up || down) return '|';
    if(left || right) return '-';
    return '#';
}


//Funcion que muestra el laberinto en consola.
void drawMaze(const Maze* maze){

    //Permite el cambio de colores en la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int y = 0; y < maze->rows; ++y) {
        for (int x = 0; x < maze->cols; ++x){
            //Obtiene el caracter actual del laberinto (x,y)
            char c = maze->grid[y][x];

            //LOGICA DE VISUALIZACION
            //Verifica si es la celda donde esta el jugador
            if(x == maze->playerX && y == maze->playerY){
                //Cambia el color a rojo.
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "♡";
            //Si es pared    
            }else if(c == '#'){
                //Cambia a color blanco.
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                //Dibuja '|' o '-', esto depende de la forma (Funcion isWallet)
                cout << typeWall(maze, y, x);
            //Si es el jefe    
            }else if(c == 'B') {
                //Cambia a color verde
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << 'B';   
            //Para cualquier otro caracter       
            }else{
                //Cambia a color blanco
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                //Imprime el caracter original
                cout << c;
            }
        }
        cout << endl;
    }

    //Restaura a los colores originales
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}