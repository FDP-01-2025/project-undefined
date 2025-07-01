#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include "../include/utils/consoleUtils.h"

using namespace std;

// === CONFIGURACIÓN DEL BANCO DE DIFERENCIAS ===
namespace {
    const pair<string, string> DIFERENCIAS[6] = {
        {"  La maromota le dijo hola al dragon que volaba sobre el cielo\n                    ║   La maromota le dijo ola al dragon que volaba sobre el cielo", "ola"},
        {"  Tengo 15 manzanas en mi canasta\n                    ║   Tengo 16 manzanas en mi canasta", "16"},
        {"  El perro corrio rapidamente al parque\n                    ║   El can corrio rapidamente al parque", "can"},
        {"  La luna brilla en el cielo\n                    ║   La luna brila en el cielo", "brila"},
        {"  El leon ruge en la selva\n                    ║   El leon ruje en la selva", "ruje"},
        {"  La casa esta lejos\n                    ║   Casa esta lejos", "La"}
    };

    int currentDifferenceIndex = 0;

    // Normalización para comparar de forma flexible
    bool checkAnswer(const string& answer, const string& correct) {
        string normalized = answer;
        transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
        normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());

        string normalizedCorrect = correct;
        transform(normalizedCorrect.begin(), normalizedCorrect.end(), normalizedCorrect.begin(), ::tolower);
        normalizedCorrect.erase(remove(normalizedCorrect.begin(), normalizedCorrect.end(), ' '), normalizedCorrect.end());

        return normalized == normalizedCorrect;
    }

    // Dibuja un marco con bordes y título opcional
    void drawFrame(int posX, int posY, int width, int height, const string& title = "") {
        moveCursor(posX, posY);
        cout << "╔";
        for (int i = 0; i < width - 2; i++) cout << "═";
        cout << "╗";
        if (!title.empty()) {
            moveCursor(posX + 2, posY);
            cout << " " << title << " ";
        }
        for (int i = 1; i < height - 1; i++) {
            moveCursor(posX, posY + i);
            cout << "║";
            moveCursor(posX + width - 1, posY + i);
            cout << "║";
        }
        moveCursor(posX, posY + height - 1);
        cout << "╚";
        for (int i = 0; i < width - 2; i++) cout << "═";
        cout << "╝";
    }

    // Centra texto dentro de un marco
    void centerTextInFrame(int frameX, int frameY, int frameWidth, int frameHeight, const string& text, int yOffset = 0) {
        int textPosX = frameX + (frameWidth - text.length()) / 2;
        int textPosY = frameY + (frameHeight / 2) + yOffset;
        moveCursor(max(frameX + 1, textPosX), textPosY);
        cout << text;
    }
}

// === FUNCIÓN PRINCIPAL DEL MINIJUEGO ===
bool playSpotDifference(int posX, int posY) {
    // Limpiar pantalla para mantener estética
    system("cls");

    // === Marco principal (verde) ===
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde
    drawFrame(posX, posY, 100, 20, " ENCUENTRA LA DIFERENCIA ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    // Verificar si se completaron todas las diferencias
    if (currentDifferenceIndex >= sizeof(DIFERENCIAS) / sizeof(DIFERENCIAS[0])) {
        currentDifferenceIndex = 0; // Reiniciar para futuras sesiones
        return true;
    }

    auto diferencia = DIFERENCIAS[currentDifferenceIndex];

    // === Marco de pregunta (rojo) ===
    int questionFrameX = posX + 5;
    int questionFrameY = posY + 3;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo
    drawFrame(questionFrameX, questionFrameY, 80, 7, " ORACIONES ");
    centerTextInFrame(questionFrameX, questionFrameY, 60, 5, "Encuentra la palabra o número diferente(palabra de abajo):");
    moveCursor(questionFrameX + 2, questionFrameY + 3);
    cout << diferencia.first;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    // === Marco de respuesta (azul) ===
    int answerFrameX = posX + 5;
    int answerFrameY = posY + 10;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // Azul
    drawFrame(answerFrameX, answerFrameY, 80, 5, " RESPUESTA ");
    moveCursor(answerFrameX + 10, answerFrameY + 2);
    cout << "> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    // Tomar la respuesta
    string respuesta;
    getline(cin, respuesta);

    // Verificar si es correcta
    bool isCorrect = checkAnswer(respuesta, diferencia.second);

    // === Marco de resultado ===
    int resultFrameX = posX + 5;
    int resultFrameY = posY + 16;

    if (isCorrect) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Verde
        drawFrame(resultFrameX, resultFrameY, 60, 3, " RESULTADO ");
        centerTextInFrame(resultFrameX, resultFrameY, 60, 3, "¡Correcto!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        currentDifferenceIndex++; // Avanza a la siguiente pregunta
        return true;
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Rojo
        drawFrame(resultFrameX, resultFrameY, 60, 3, " RESULTADO ");
        string resultText = "Incorrecto. Era: " + diferencia.second;
        centerTextInFrame(resultFrameX, resultFrameY, 60, 3, resultText);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }
}
