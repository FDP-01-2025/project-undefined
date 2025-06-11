#include "maze.h" // 
#include <stdio.h> //Libreria que permite acceder a archivos externos (FILE)
#include <string.h>
#include <iostream>
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

//Funcion que muestra el laberinto en consola.
void drawMaze(const Maze* maze){
    for(int i = 0; i < maze->rows; ++i){
        cout << "\n" << maze->grid[i]; 
    }
}