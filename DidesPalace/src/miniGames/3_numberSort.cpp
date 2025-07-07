#include "minigames/3_numberSort.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include "../include/utils/consoleUtils.h"
#include "../include/utils/sounds.h"

using namespace std;

namespace
{
   
    // Number list
    const vector<pair<string, string>> LIST = {
        {"Ordena los siguientes numeros: 3-1-2-4", "1-2-3-4"},
        {"Ordena los siguientes numeros: 5-3-7-1", "1-3-5-7"},
        {"Ordena los siguientes numeros: 20-10-5-15", "5-10-15-20"},
        {"Ordena los siguientes numeros: 2-8-4-6", "2-4-6-8"},
        {"Ordena los siguientes numeros: 11-3-7-5", "3-5-7-11"},
        {"Ordena los siguientes numeros: 9-1-7-5", "1-5-7-9"},
        {"Ordena los siguientes numeros: 16-4-1-9", "1-4-9-16"},
        {"Ordena los siguientes numeros: 13-17-2-19", "2-13-17-19"},
        {"Ordena los siguientes numeros: 25-10-5-20", "5-10-20-25"},
        {"Ordena los siguientes numeros: 3-2-1-4", "1-2-3-4"},
        {"Ordena los siguientes numeros: 81-9-27-3", "3-9-27-81"},
        {"Ordena los siguientes numeros: 7-5-3-1", "1-3-5-7"},
        {"Ordena los siguientes numeros: 100-10-1000-1", "1-10-100-1000"},
        {"Ordena los siguientes numeros: 64-8-16-4", "4-8-16-64"},
        {"Ordena los siguientes numeros: 7-28-21-14", "7-14-21-28"},
        {"Ordena los siguientes numeros: 6-36-18-12", "6-12-18-36"},
        {"Ordena los siguientes numeros: 49-25-9-1", "1-9-25-49"},
        {"Ordena los siguientes numeros: 15-5-10-20", "5-10-15-20"},
        {"Ordena los siguientes numeros: 4-3-2-1", "1-2-3-4"},
        {"Ordena los siguientes numeros: 100-50-25-75", "25-50-75-100"},
        {"Ordena los siguientes numeros: 121-36-81-49", "36-49-81-121"},
        {"Ordena los siguientes numeros: 30-10-50-40", "10-30-40-50"},
        {"Ordena los siguientes numeros: 6-3-9-12", "3-6-9-12"},
        {"Ordena los siguientes numeros: 24-16-32-8", "8-16-24-32"}};

    // Random order of Number list
    vector<pair<string, string>> LIST_RANDOM;
    bool LIST_RANDOM_INICIALIZED = false;
    // variable to move the index
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
    drawFrame(posX, posY, 60, 20, " ORDENAR NUMEROS (Separalos con '-')");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset to default


    playBossMusic();
    // Only shuffle once at the beginning
    if (!LIST_RANDOM_INICIALIZED)
    {
        LIST_RANDOM = LIST; // Copy from original
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        shuffle(LIST_RANDOM.begin(), LIST_RANDOM.end(), default_random_engine(seed));
        LIST_RANDOM_INICIALIZED = true;
        currentQuestionIndex = 0;
    }

    if (currentQuestionIndex >= LIST_RANDOM.size())
    {
        // All questions used, restart or end
        LIST_RANDOM_INICIALIZED = false;
        return true;
    }

    auto pregunta = LIST_RANDOM[currentQuestionIndex];
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

    const int durationSeconds = 15;
    DWORD startTime = GetTickCount();

    int remainingSeconds = durationSeconds;
    string input = ""; // Store typed input here
    int lastShown = durationSeconds + 1;

    while (true)
    {
        DWORD now = GetTickCount();
        DWORD elapsed = now - startTime;
        int secondsPassed = elapsed / 1000;
        remainingSeconds = durationSeconds - secondsPassed;

        // Update countdown only if it has changed
        if (remainingSeconds != lastShown && remainingSeconds >= 0)
        {
            if (remainingSeconds >= 10)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                moveCursor(answerFrameX + 60, answerFrameY - 10);
                cout << "                            "; // Clear previous text
                moveCursor(answerFrameX + 60, answerFrameY - 10);
                cout << remainingSeconds << " segundos restantes...";
                lastShown = remainingSeconds;
            }
            else if (remainingSeconds > 5)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                moveCursor(answerFrameX + 60, answerFrameY - 10);
                cout << "                              "; // Clear previous text
                moveCursor(answerFrameX + 60, answerFrameY - 10);
                cout << remainingSeconds << " segundos restantes...";
                lastShown = remainingSeconds;
            }else{
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                moveCursor(answerFrameX + 60, answerFrameY - 10);
                cout << "                              "; // Clear previous text
                moveCursor(answerFrameX + 60, answerFrameY - 10);
                cout << remainingSeconds << " segundos restantes...";
                lastShown = remainingSeconds;
            }   
        }

        // Show current input
        moveCursor(answerFrameX + 12, answerFrameY + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        cout << "> " << input << " \b"; // Display user input

        // Check for non-blocking key press
        if (_kbhit())
        {
            char c = _getch();

            // If Enter is pressed, finish input
            if (c == '\r')
            {
                break;
            }
            // Handle backspace
            else if (c == 8 && !input.empty())
            {
                input.pop_back();
                moveCursor(answerFrameX + 12 + input.length(), answerFrameY + 2);
                cout << " \b";
            }
            // Add printable character to input
            else if (isprint(c))
            {
                input += c;
            }
        }

        // If time is up, break the loop
        if (remainingSeconds <= 0)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            moveCursor(answerFrameX + 60, answerFrameY - 10);
            cout << "                              "; // Clear previous text
            moveCursor(answerFrameX + 60, answerFrameY - 10);
            cout << "¡Tiempo terminado!\n";
            break;
        }

        Sleep(50); // Small delay to reduce CPU usage
    }
    // Verify answer
    bool isCorrect = checkAnswer(input, pregunta.second);

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
        string resultText = "La respuesta era: " + pregunta.second;
        centerTextInFrame(resultFrameX, resultFrameY, 50, 3, resultText);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        return false;
    }
}