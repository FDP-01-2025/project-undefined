#include "minigames/3_numberSort.h"
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

namespace
{
    // Number list
    const vector<pair<string, string>> LISTA = {
        {"Ordena los siguientes numeros: 3, 1, 2, 4", "1, 2, 3, 4"},
        {"Ordena los siguientes numeros: 5, 3, 7, 1", "1, 3, 5, 7"},
        {"Ordena los siguientes numeros: 20, 10, 5, 15", "5, 10, 15, 20"},
        {"Ordena los siguientes numeros: 2, 8, 4, 6", "2, 4, 6, 8"}};

    // Variable para llevar el progreso
    int currentQuestionIndex = 0;

    bool checkAnswer(const string &answer, const string &correct)
    {
        string normalized = answer;
        transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
        normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());
        return normalized == correct;
    }

    // Function to draw a framed box
    void drawFrame(int posX, int posY, int width, int height, const string &title = "")
    {
        // Top border
        moveCursor(posX, posY);
        cout << "╔";
        for (int i = 0; i < width - 2; i++)
            cout << "═";
        cout << "╗";

        // Title if exists
        if (!title.empty())
        {
            moveCursor(posX + 2, posY);
            cout << " " << title << " ";
        }

        // Side borders
        for (int i = 1; i < height - 1; i++)
        {
            moveCursor(posX, posY + i);
            cout << "║";
            moveCursor(posX + width - 1, posY + i);
            cout << "║";
        }

        // Bottom border
        moveCursor(posX, posY + height - 1);
        cout << "╚";
        for (int i = 0; i < width - 2; i++)
            cout << "═";
        cout << "╝";
    }

    // Function to center text in a frame
    void centerTextInFrame(int frameX, int frameY, int frameWidth, int frameHeight, const string &text, int yOffset = 0)
    {
        int textPosX = frameX + (frameWidth - text.length()) / 2;
        int textPosY = frameY + (frameHeight / 2) + yOffset;
        moveCursor(max(frameX + 1, textPosX), textPosY);
        cout << text;
    }
}

bool playNumberSort(int posX, int posY)
{
    // Clear area for our frames
    system("cls");

    // Draw main container frame (green)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green text
    drawFrame(posX, posY, 60, 20, " ORDENAR NUMEROS ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default

    // Verificar si ya se respondieron todos los items
    if (currentQuestionIndex >= LISTA.size())
    {
        currentQuestionIndex = 0; // Reiniciar para futuras batallas
        return true;
    }

    // Obtener la pregunta actual (en orden)
    auto pregunta = LISTA[currentQuestionIndex];

    // Draw question frame (red)
    int questionFrameX = posX + 5;
    int questionFrameY = posY + 3;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red text
    drawFrame(questionFrameX, questionFrameY, 50, 5, " PREGUNTA ");
    centerTextInFrame(questionFrameX, questionFrameY, 50, 5, pregunta.first);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default

    // Draw answer input frame (blue)
    int answerFrameX = posX + 5;
    int answerFrameY = posY + 10;
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
    int resultFrameX = posX + 5;
    int resultFrameY = posY + 16;

    if (isCorrect)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green for correct
        drawFrame(resultFrameX, resultFrameY, 50, 3, " RESULTADO ");
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, "¡Correcto!");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        // Avanzar a la siguiente pregunta solo si la respuesta fue correcta
        currentQuestionIndex++;
        return true;
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Red for incorrect
        drawFrame(resultFrameX, resultFrameY, 50, 3, " RESULTADO ");
        string resultText = "¡Incorrecto! La respuesta era: " + pregunta.second;
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, resultText);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }
}