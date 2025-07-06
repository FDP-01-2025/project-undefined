#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include "../include/utils/consoleUtils.h"

using namespace std;

const int WIDTH = 100; // Width of the game area
const int HEIGHT = 20; // Height of the game area


// === SPOT THE DIFFERENCE DATABASE CONFIGURATION ===
namespace {
    const pair<string, string> DIFERENCIAS[6] = {
        {"  La maromota le dijo hola al dragon que volaba sobre el cielo\n                              ║    La maromota le dijo ola al dragon que volaba sobre el cielo", "ola"},
        {"  Tengo 15 manzanas en mi canasta\n                              ║    Tengo 16 manzanas en mi canasta", "16"},
        {"  El perro corrio rapidamente al parque\n                              ║    El can corrio rapidamente al parque", "can"},
        {"  La luna brilla en el cielo\n                              ║    La luna brila en el cielo", "brila"},
        {"  El leon ruge en la selva\n                              ║    El leon ruje en la selva", "ruje"},
        {"  La casa esta lejos\n                              ║    Casa esta lejos", "La"}
    };

    int currentDifferenceIndex = 0;

    // Normalization for case-insensitive and space-ignoring comparison
    bool checkAnswer(const string& answer, const string& correct) {
        string normalized = answer;
        transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
        normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());

        string normalizedCorrect = correct;
        transform(normalizedCorrect.begin(), normalizedCorrect.end(), normalizedCorrect.begin(), ::tolower);
        normalizedCorrect.erase(remove(normalizedCorrect.begin(), normalizedCorrect.end(), ' '), normalizedCorrect.end());

        return normalized == normalizedCorrect;
    }

    // Draws a box frame with optional title
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

    // Centers text vertically and horizontally within a frame
    void centerTextInFrame(int frameX, int frameY, int frameWidth, int frameHeight, const string& text, int yOffset = 0) {
        int textPosX = frameX + (frameWidth - text.length()) / 2;
        int textPosY = frameY + (frameHeight / 2) + yOffset;
        moveCursor(max(frameX + 1, textPosX), textPosY);
        cout << text;
    }
}

// === MAIN MINIGAME FUNCTION ===
bool playSpotDifference(int posX, int posY) {
    // Clear screen before drawing
    system("cls");

    // Calculate coordinates to center the game frame
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startX = (consoleWidth - WIDTH) / 2;
    int startY = (consoleHeight - HEIGHT) / 2 - 1;

    // === Main container frame (green) ===
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    drawFrame(startX, startY, WIDTH , HEIGHT, " ENCUENTRA LA DIFERENCIA ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    // Check if we've shown all differences
    if (currentDifferenceIndex >= sizeof(DIFERENCIAS) / sizeof(DIFERENCIAS[0])) {
        currentDifferenceIndex = 0; // Reset index for replayability
        return true;
    }

    auto diferencia = DIFERENCIAS[currentDifferenceIndex];

    // === Question display frame (red) ===
    int questionFrameX = startX + 5;
    int questionFrameY = startY + 3;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    drawFrame(questionFrameX, questionFrameY, 80, 7, " ORACIONES ");
    centerTextInFrame(questionFrameX, questionFrameY, 70, 5, "Encuentra la palabra o número diferente (palabra de abajo):");
    moveCursor(questionFrameX + 3, questionFrameY + 3);
    cout << diferencia.first;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    // === Answer input frame (blue) ===
    int answerFrameX = startX + 5;
    int answerFrameY = startY + 10;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    drawFrame(answerFrameX, answerFrameY, 80, 5, " RESPUESTA ");
    moveCursor(answerFrameX + 6, answerFrameY + 2);
    cout << "> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    // Get player's answer input
    string respuesta;
    getline(cin, respuesta);

    // Check if answer matches the difference
    bool isCorrect = checkAnswer(respuesta, diferencia.second);

    // === Result display frame ===
    int resultFrameX = startX + 5;
    int resultFrameY = startY + 16;

    if (isCorrect) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        drawFrame(resultFrameX, resultFrameY, 60, 3, " RESULTADO ");
        centerTextInFrame(resultFrameX, resultFrameY, 60, 3, "¡Correcto!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        currentDifferenceIndex++; // Advance to next difference
        return true;
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        drawFrame(resultFrameX, resultFrameY, 60, 3, " RESULTADO ");
        string resultText = "Incorrecto. Era: " + diferencia.second;
        centerTextInFrame(resultFrameX, resultFrameY, 60, 3, resultText);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }
}