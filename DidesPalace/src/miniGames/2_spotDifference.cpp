#include <iostream>
#include <string>
#include <windows.h>
#include "../include/utils/consoleUtils.h" // Ajusta la ruta según tu estructura
using namespace std;

// Esta versión acepta coordenadas para mostrarse dentro del marco RPG
bool playSpotDifference(int posX = 0, int posY = 0) {
    string sentence1 = "La maromota le dijo hola al dragon que volaba sobre el cielo";
    string sentence2 = "La maromota le dijo ola al dragon que volaba sobre el cielo";

    // Limpiar la zona donde se dibujará el minijuego
    for (int i = 0; i < 7; ++i) {
        moveCursor(posX, posY + i);
        cout << string(60, ' ');
    }

    // Mostrar minijuego dentro del marco RPG
    moveCursor(posX, posY);     cout << "=== Encuentra la diferencia ===";
    moveCursor(posX, posY + 1); cout << "Oración 1: " << sentence1;
    moveCursor(posX, posY + 2); cout << "Oración 2: " << sentence2;
    moveCursor(posX, posY + 4); cout << "¿Qué palabra es diferente en la oración 2?";
    moveCursor(posX, posY + 5); cout << "Tu respuesta: ";

    string input;
    getline(cin, input);

    // Limpiar área
    for (int i = 0; i < 7; ++i) {
        moveCursor(posX, posY + i);
        cout << string(60, ' ');
    }

    return (input == "Hola" || input == "ola");
}
