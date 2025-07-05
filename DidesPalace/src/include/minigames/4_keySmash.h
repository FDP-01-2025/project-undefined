#pragma once

const int WIDTH = 40; //Ancho del area del juego
const int HEIGHT = 20; //Alto del area del juego
const int NUM_KEYS = 5; //Letras activas simultaneas

//Estructura para representar una  letra
struct Key{
    //Guarda la letra
    char letter;
    //Coordenadas de la letra en el area del juego
    int x, y;
    //Indica si la letra esta activa
    bool active;
};

//Funciones a implementar
bool playKeySmash(int posX = 0, int posY = 0);
//Función que genera una letra aleatoria entre 'A' y 'Z'
char getRandomKey(); 
//Función que dibuja un marco en el area del juego
void drawFrame(int posX, int posY);
