#include "minigames/1_riddles.h"
#include "bosses.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <windows.h>
#include "utils/consoleUtils.h"

using namespace std;
using namespace std::chrono;

namespace {
    // Question bank
    const vector<pair<string, string>> PREGUNTAS = {
        {"¿Capital de Francia?", "paris"},
        {"¿2 + 2?", "4"},
        {"¿Color del cielo?", "azul"},
        {"¿Animal que maúlla?", "gato"},
        {"¿Opuesto a día?", "noche"}
    };

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
    system("cls"); // Or use more precise clearing if needed

    // Draw main container frame
    drawFrame(posX, posY, 60, 20, " ADIVINANZA ");

    // Select random question
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, PREGUNTAS.size() - 1);
    auto pregunta = PREGUNTAS[dist(gen)];

    // Draw question frame (centered in main frame)
    int questionFrameX = posX + 5;
    int questionFrameY = posY + 3;
    drawFrame(questionFrameX, questionFrameY, 50, 5, " PREGUNTA ");
    centerTextInFrame(questionFrameX, questionFrameY, 50, 5, pregunta.first);

    // Draw answer input frame
    int answerFrameX = posX + 5;
    int answerFrameY = posY + 10;
    drawFrame(answerFrameX, answerFrameY, 50, 5, " RESPUESTA ");
    moveCursor(answerFrameX + 10, answerFrameY + 2);
    cout << "> ";

    // Get answer with timer
    auto start = high_resolution_clock::now();
    string respuesta;
    getline(cin, respuesta);
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<seconds>(end - start);

    // Verify answer
    bool isCorrect = checkAnswer(respuesta, pregunta.second);
    bool timeOut = elapsed.count() >= 15;  // 15 second limit

    // Draw result frame
    int resultFrameX = posX + 5;
    int resultFrameY = posY + 16;
    drawFrame(resultFrameX, resultFrameY, 50, 3, " RESULTADO ");

    if (timeOut) {
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, "¡Tiempo agotado!");
        return false;
    } else if (isCorrect) {
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, "¡Correcto!");
        return true;
    } else {
        string resultText = "¡Incorrecto! La respuesta era: " + pregunta.second;
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, resultText);
        return false;
    }
}