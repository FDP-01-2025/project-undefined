#include <windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "utils/sounds.h"
#include "utils/consoleUtils.h"

using namespace std;

// Function to display history with centered art and text
bool showStory() {

    //Play the music of the story
    playStory();
    system("cls");

    //To center the text in the console
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int currentY = 2; // Empieza en la fila 2

    string art[] = {
        "              |>>>                  |>>>",
        "              |                     |",
        "          _  _|_  _             _  _|_  _",
        "         | |_| |_| |           | |_| |_| |",
        "         \\  .      /           \\ .    .  /",
        "          \\    ,  /             \\   ,   /",
        "           |   | |               | |   |",
        "        __/     |__           __/ |     \\__",
        "       |         |           |    |        |",
        "       |  DICES  |           |  PALACE    |",
        "       |_________|           |____________|",
        ""
    };

    //Color of the castle ascci
    setColor(6);
    for (int i = 0; i < sizeof(art) / sizeof(art[0]); ++i) {
        int x = (consoleWidth - art[i].length()) / 2;

        moveCursor(x, currentY);

        cout << art[i] << flush;
        ++currentY;
        Sleep(50);
    }

    // Small pause before of write the story
    Sleep(500); 
    ++currentY;

    string story[] = {
        "Hace mucho tiempo, en un reino oculto tras dados encantados...",
        "Un castillo surgió de la nada, conocido como el Palacio de los Dados.",
        "",
        "Pero esta historia no comienza ahí...",
        "Se centra en la travesía de un ladrón moderno que roba un casino.",
        "Sin embargo, al lograr su objetivo, una fuerza extraña lo teletransporta",
        "a un castillo en plena época medieval, rodeado de piedra, oscuridad y magia.",
        "",
        "Sin pistas de dónde está ni cómo llegó, comienza su búsqueda por sobrevivir y escapar.",
        "En lo profundo del castillo, le esperan decisiones, caminos inciertos y enemigos ocultos.",
        "",
        "Criaturas pixeladas, jefes enigmáticos, acertijos antiguos...",
        "Y tú, valiente jugador, eres el elegido para romper la maldición del palacio.",
        "",
        "¿Podrá volver a su tiempo, o quedará atrapado en el Palacio de los Dados para siempre?",
        "",
    };

    //Color of the text
    setColor(14);
    for (int i = 0; i < sizeof(story) / sizeof(story[0]); ++i) {
        int x = (consoleWidth - story[i].length()) / 2;

        moveCursor(x, currentY);

        for (size_t j = 0; j < story[i].length(); ++j) {
            cout << story[i][j] << flush;
            Sleep(30);
        }

        ++currentY;
        Sleep(250);
    }

    // Restore colors
    setColor(7);
    moveCursor(10, 80);
    system("pause");

    //Back to the menu
    return false;
}