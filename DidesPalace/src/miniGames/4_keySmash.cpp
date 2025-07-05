#include "minigames/4_keySmash.h"
#include <iostream>
#include <windows.h>
#include "conio.h" // Librería para manejo de entrada de teclado
#include <ctime>   // Para generar números aleatorios
#include <cstdlib>
#include "../include/utils/consoleUtils.h"
using namespace std;

// Permite acceder a la consola de windows (Manipular cursos y colores))
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Genera una letra aleatoria entre 'A' y 'Z'
char getRandomKey()
{
    return 'A' + rand() % 26;
}

// Dibuja un marco en el área del juego
void drawFrame(int PosX, int PosY)
{
    setColor(11);

    // Dibuja el marco de los bordes horizontales
    for (int i = 0; i <= WIDTH; i++)
    {
        moveCursor(PosX + i, PosY);
        cout << "#";
        moveCursor(PosX + i, PosY + HEIGHT + 1);
        cout << "#";
    }

    // Dibuja el marco de los bordes verticales
    for (int i = 0; i <= HEIGHT + 1; i++)
    {
        moveCursor(PosX, PosY + i);
        cout << "#";
        moveCursor(PosX + WIDTH, PosY + i);
        cout << "#";
    }
}

bool playKeySmash(int posX, int posY)
{
    // Clear the console
    system("cls");
    // Inicializa los numeros aleatorios
    srand(time(0));

    // Se calculan las coordenadas para centrar el marco de la consola
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startX = (consoleWidth - WIDTH) / 2;
    int startY = (consoleHeight - HEIGHT) / 2 - 1;

    // Dibuja el marco un pixel antes para encerrar el area del juego
    drawFrame(startX - 1, startY - 1);

    // FUNCIONAMINETO DEL JUEGO
    // Arreglo de 5 letras que caeran simultaneamente
    Key keys[NUM_KEYS];

    // Inicializa el puntaje
    int score = 0;
    // Inicializa la velocidad inicial
    int speed = 300;
    // Inicializa el temporizador
    DWORD lastSpeedUp = GetTickCount();

    // Inicializa las letras en posiciones aleatorias dentro del area del juego
    for (int i = 0; i < NUM_KEYS; i++)
    {
        keys[i].letter = getRandomKey();
        keys[i].x = startX + 1 + rand() % (WIDTH - 2);
        keys[i].y = startY;
        keys[i].active = true;
    }

    // Borra la letra anterior antes de dibujar la nueva
    while (true)
    {
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].active && keys[i].y > startY)
            {
                moveCursor(keys[i].x, keys[i].y - 1), cout << " ";
            }
        }

        // Dibuja letras nuevas
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].active)
            {
                moveCursor(keys[i].x, keys[i].y);
                setColor(14);
                cout << keys[i].letter;
            }
        }

        // Captura la tecla presionada
        if (_kbhit())
        {
            char keyPressed = toupper(_getch()); // Captura la tecla presionada y la convierte a mayúscula
            for (int i = 0; i < NUM_KEYS; i++)
            {
                if (keys[i].active && keyPressed == keys[i].letter)
                {
                    moveCursor(keys[i].x, keys[i].y);
                    cout << " "; // Borra la letra correcta
                    score++;
                    keys[i].letter = getRandomKey(); // Genera una nueva letra
                    keys[i].x = startX + 1 + rand() % (WIDTH - 2);
                    keys[i].y = startY; // Reinicia la posición vertical de la letra
                }
            }
        }

        // Mueve la letra hacia abajo
        for (int i = 0; i < NUM_KEYS; i++)
        {
            if (keys[i].active)
            {
                keys[i].y++;
                // Si la letra llega al final del área del juego, se considera un fallo
                if (keys[i].y > startY + HEIGHT)
                {
                    setColor(12);
                    moveCursor(startX, startY + HEIGHT + 3);
                    cout << "¡Fallaste! Puntos: " << score;
                    moveCursor(startX, startY + HEIGHT + 4);
                    cout << "Presiona una tecla para continuar...";
                    _getch();
                    return false; // Termina el juego
                }
            }
        }

        // Muestra el puntaje actual
        moveCursor(startX, startY + HEIGHT + 2);
        setColor(10);
        cout << "Puntaje: " << score << "    ";

        // Si el puntaje llega a 50, el jugador gana
        if (score >= 50) 
        {
            setColor(10);
            moveCursor(startX, startY + HEIGHT + 3);
            cout << "¡Felicidades! Has ganado con " << score << " puntos.";
            moveCursor(startX, startY + HEIGHT + 4);
            cout << "Presiona una tecla para continuar...";
            _getch();
            return true; // Termina el juego
        }

        // Actualiza la velocidad del juego cada 15 segundos
        if (GetTickCount() - lastSpeedUp >= 15000 && speed > 50)
        {
            speed -= 50;
            lastSpeedUp = GetTickCount();
        }

        Sleep(speed); // Controla la velocidad del juego
    }
}