#include <iostream>
#include <locale.h>
#include <windows.h>
// Captura letras sin esperar el enter
#include <conio.h>
#include "utils/menu.h"
#include "levels/level1.h"
#include "levels/level2.h"
#include "levels/level3.h"
#include "levels/level4.h"

using namespace std;

int main()
{

    // Permite mostrar caracteres especiales
    SetConsoleOutputCP(CP_UTF8);

    // Se ejecuta este bloque de codigo siempre, a menos que se presione esc.
    while (true)
    {
        system("cls");
        showMenu();

        char option = _getch();
        // Bandera que permitira salir o no del juego
        // Si quitGame es true sale del juego (Cuando se presiona esc)
        // Si quitGame es false sigue en el juego
        bool quitGame = false;

        switch (option)
        {
        case '1':
            quitGame = Level1();
            break;
        case '2':
            quitGame = Level2();
            break;
        case '3':
            quitGame = Level3();
            break;
         case '4':
            quitGame = Level4();
            break;    
        // Tecla ESC
        case 27:
            quitGame = true;
            break;
        }

        // Si quitGame es verdadera sale del bucle
        if (quitGame)
        {
            cout << "\nSaliendo del juego...\n";
            // Se sale del bucle
            break;
        }
    }

    return 0;
}