#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "minigames/2_spotDifference.h"
#include "utils/consoleUtils.h"
using namespace std;

const int FRAME_WIDTH = 90;
const int FRAME_HEIGHT = 25;

// Variables del jugador
int playerHealth = 100;
int playerDamage = 10;

// ================= Funciones visuales reutilizadas ===================

// Función para dibujar el marco de batalla
void drawBattleFrame() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    for (int i = 0; i < FRAME_WIDTH; ++i) {
        moveCursor(5 + i, 1); cout << "-";
        moveCursor(5 + i, FRAME_HEIGHT); cout << "-";
    }
    for (int i = 1; i <= FRAME_HEIGHT; ++i) {
        moveCursor(5, i); cout << "|";
        moveCursor(5 + FRAME_WIDTH - 1, i); cout << "|";
    }
    moveCursor(5, 1); cout << "+";
    moveCursor(5 + FRAME_WIDTH - 1, 1); cout << "+";
    moveCursor(5, FRAME_HEIGHT); cout << "+";
    moveCursor(5 + FRAME_WIDTH - 1, FRAME_HEIGHT); cout << "+";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Función para mostrar un mensaje centrado en un recuadro
void mostrarMensaje(const string& mensaje) {
    int ancho = 50, alto = 5;
    int x = 10 + (FRAME_WIDTH - ancho) / 2;
    int y = 10;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    // Dibujar recuadro
    for (int i = 0; i < ancho; ++i) {
        moveCursor(x + i, y); cout << "-";
        moveCursor(x + i, y + alto - 1); cout << "-";
    }
    for (int i = 0; i < alto; ++i) {
        moveCursor(x, y + i); cout << "|";
        moveCursor(x + ancho - 1, y + i); cout << "|";
    }

    // Esquinas
    moveCursor(x, y); cout << "+";
    moveCursor(x + ancho - 1, y); cout << "+";
    moveCursor(x, y + alto - 1); cout << "+";
    moveCursor(x + ancho - 1, y + alto - 1); cout << "+";

    // Mensaje
    moveCursor(x + 2, y + alto / 2);
    cout << mensaje;

    moveCursor(x + 2, y + alto - 1);
    cout << "Presiona una tecla para continuar...";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    _getch();

    // Limpiar mensaje
    for (int i = 0; i < alto; ++i) {
        moveCursor(x, y + i);
        for (int j = 0; j < ancho; ++j) cout << " ";
    }
}

// Función para cargar arte ASCII desde archivo externo
void mostrarArteJefe(const string& path, int x, int y) {
    ifstream file(path);
    string linea;
    int offsetY = 0;
    while (getline(file, linea)) {
        moveCursor(x, y + offsetY);
        cout << linea;
        offsetY++;
    }
}

// ==================== Lógica de la batalla ====================

void bossBattleRPG() {
    int bossHP = 1;
    int playerHP = 100;
    bool bossDefeated = false;

    consoleSettings();
    consoleCenter();
    system("cls");
    drawBattleFrame();

    while (bossHP > 0 && playerHP > 0) {
        system("cls");
        drawBattleFrame();

        // Mostrar arte ASCII del jefe
        mostrarArteJefe("data/bosses/boss2.txt", 10, 3);

        // Mostrar estadísticas
        moveCursor(60, 5);  cout << "╔══════════════╗";
        moveCursor(60, 6);  cout << "║  Jefe: ???   ║";
        moveCursor(60, 7);  cout << "║ HP: " << bossHP << "         ║";
        moveCursor(60, 8);  cout << "╚══════════════╝";

        moveCursor(60, 10); cout << "╔══════════════╗";
        moveCursor(60, 11); cout << "║  Tú          ║";
        moveCursor(60, 12); cout << "║ HP: " << playerHP << "       ║";
        moveCursor(60, 13); cout << "╚══════════════╝";

        // Opciones
        moveCursor(20, 20);
        cout << "[1] Atacar (Mini juego)   [2] Defender   [3] Huir";
        moveCursor(20, 22);
        cout << "Elige una opción: ";

        char opcion = _getch();

        if (opcion == '1') {
            // Limpiar zona de opciones
            for (int y = 20; y <= 23; ++y) {
                moveCursor(20, y);
                cout << string(50, ' ');
            }

            // Ejecutar el minijuego dentro del marco (modo integrado)
            bool ganaste = playSpotDifference(20, 20);  // zona visual en el marco

            if (ganaste) {
                bossHP = 0;
                bossDefeated = true;
                mostrarMensaje("¡Has derrotado al jefe con tu inteligencia!");
            } else {
                playerHP -= 20;
                mostrarMensaje("Fallaste el minijuego... el jefe te ha golpeado.");
            }
        } else if (opcion == '2') {
            playerHP += 5;
            if (playerHP > 100) playerHP = 100;
            mostrarMensaje("Te has defendido y recuperado 5 de vida.");
        } else if (opcion == '3') {
            mostrarMensaje("¡Has huido de la batalla!");
            return;
        } else {
            mostrarMensaje("Opción no válida.");
        }

        if (playerHP <= 0) {
            mostrarMensaje("Has sido derrotado...");
            exit(0);
        }
    }

    if (bossDefeated) {
        mostrarMensaje("¡Victoria! El jefe ha sido vencido.");
    }
}
