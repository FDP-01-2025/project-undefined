#include "minigames/1_riddles.h"
#include "bosses.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <windows.h>
#include "utils/consoleUtils.h" // console adaptation//
#include "../include/utils/sounds.h" // sounds included// 

using namespace std;
using namespace std::chrono;

const int WIDTH = 60; // Width of the game area
const int HEIGHT = 20; // Height of the game area

namespace {
    // Question bank (replaced vector with array)
    const pair<string, string> PREGUNTAS[8] = {
        {"¿2 + 2?", "4"},
        {"¿Color del cielo?", "azul"},
        {"¿Animal que maúlla?", "gato"},
        {"¿Opuesto a día?", "noche"},
        {"¿Líquido vital para los seres humanos?", "agua"},
        {"¿Fruto rojo con semillas externas?", "fresa"},
        {"¿Instrumento musical de 6 cuerdas?", "guitarra"},
        {"¿Órgano que bombea sangre?", "corazon"}
    };

    // Variable to track question progress

    bool checkAnswer(const string& answer, const string& correct) {
        string normalized = answer;
        transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
        normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());
        return normalized == correct;
    }

    // Function to draw a framed box
    void drawFrame(int posX, int posY, int width, int height, const string& title = "") {
        // Top border
        moveCursor(posX, posY);
        cout << "╔";
        for (int i = 0; i < width - 2; i++) cout << "═";
        cout << "╗";

        // Title if exists
        if (!title.empty()) {
            moveCursor(posX + 2, posY);
            cout << " " << title << " ";
        }

        // Side borders
        for (int i = 1; i < height - 1; i++) {
            moveCursor(posX, posY + i);
            cout << "║";
            moveCursor(posX + width - 1, posY + i);
            cout << "║";
        }

        // Bottom border
        moveCursor(posX, posY + height - 1);
        cout << "╚";
        for (int i = 0; i < width - 2; i++) cout << "═";
        cout << "╝";
    }

    // Function to center text in a frame
    void centerTextInFrame(int frameX, int frameY, int frameWidth, int frameHeight, const string& text, int yOffset = 0) {
        int textPosX = frameX + (frameWidth - text.length()) / 2;
        int textPosY = frameY + (frameHeight / 2) + yOffset;
        moveCursor(max(frameX + 1, textPosX), textPosY);
        cout << text;
    }
}

bool playriddles(int posX, int posY) {
    // Clear area for our frames
    system("cls");

    // Funcion to show an animated message (Title of the game)
    int numQuestion = currentQuestionIndex + 1;
    showAnimatedMessage("<<<< RIDDLES GAME - Pregunta #" + to_string(numQuestion) + " >>>>" + "\nAdivina las respuestas correctas", 50, 1500);

    playBossMusic();
    // Calculate coordinates to center the game frame
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();
    int startX = (consoleWidth - WIDTH) / 2;
    int startY = (consoleHeight - HEIGHT) / 2 - 1;

    // Draw main container frame (green)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green text
    drawFrame(startX, startY, WIDTH, HEIGHT, " ADIVINANZA ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default

    // Check if all questions have been answered (changed size() to array size calculation)
    if (currentQuestionIndex >= sizeof(PREGUNTAS)/sizeof(PREGUNTAS[0])) {
        currentQuestionIndex = 0; // Reset for future battles
        return true;
    }

    // Get current question (in order)
    auto pregunta = PREGUNTAS[currentQuestionIndex];

    // Draw question frame (red)
    int questionFrameX = startX + 5;
    int questionFrameY = startY+ 3;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red text
    drawFrame(questionFrameX, questionFrameY, 50, 5, " PREGUNTA ");
    centerTextInFrame(questionFrameX, questionFrameY, 50, 5, pregunta.first);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default

    // Draw answer input frame (blue)
    int answerFrameX = startX + 5;
    int answerFrameY = startY + 10;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // Blue text
    drawFrame(answerFrameX, answerFrameY, 50, 5, " RESPUESTA ");
    moveCursor(answerFrameX + 10, answerFrameY + 2);
    cout << "> ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default for input

    // Get answer
    string respuesta;
    getline(cin, respuesta);

    // Verify answer
    bool isCorrect = checkAnswer(respuesta, pregunta.second);

    // Draw result frame
    int resultFrameX = startX + 5;
    int resultFrameY = startY + 16;
    
    if (isCorrect) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green for correct
        drawFrame(resultFrameX, resultFrameY, 50, 3, " RESULTADO ");
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, "¡Correcto!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        
        // Move to next question only if answer was correct
        currentQuestionIndex++;
        return true;
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red for incorrect
        drawFrame(resultFrameX, resultFrameY, 50, 3, " RESULTADO ");
        string resultText = "¡Incorrecto! La respuesta era: " + pregunta.second;
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, resultText);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }
}