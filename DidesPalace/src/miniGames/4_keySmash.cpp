#include "minigames/4_keySmash.h"
#include <iostream>
#include <windows.h>
using namespace std;

bool playKeySmash(int posX, int posY)
{
    // Clear the console
    system("cls");

    // Draw the title
    cout << "========= KEY SMASH =========\n";
    cout << "Presiona las teclas en el orden correcto!\n\n";

    // Instructions
    cout << "Instrucciones:\n";
    cout << "1. Presiona las teclas que aparecen en pantalla.\n";
    cout << "2. Debes presionar las teclas en el orden correcto.\n";
    cout << "3. Si fallas, el juego termina.\n\n";

    // Start the game
    cout << "¡Comienza el juego!\n";

    return true; // Placeholder for actual game logic
}