#include <windows.h>
#include <utils/consoleUtils.h>

// // Función para mover el cursor
void moveCursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para configurar la consola
void consoleSettings()
{
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_SHOWDEFAULT);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {static_cast<SHORT>(WINDOW_WIDHT), static_cast<SHORT>(WINDOW_HEIGHT)};
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT ventana = {0, 0, static_cast<SHORT>(WINDOW_WIDHT - 1), static_cast<SHORT>(WINDOW_HEIGHT - 1)};
    SetConsoleWindowInfo(hOut, TRUE, &ventana);
}

// Función para centrar la ventana
void consoleCenter()
{
    HWND hwnd = GetConsoleWindow();
    if (!hwnd)
        return;

    RECT screen;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &screen, 0);
    int screenWidht = screen.right - screen.left;
    int screenHeight = screen.bottom - screen.top;

    RECT rect;
    GetWindowRect(hwnd, &rect);
    int windowWidht = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    int posX = (screenWidht - windowWidht) / 2;
    int posY = (screenHeight - windowHeight) / 2;

    MoveWindow(hwnd, posX, posY, windowWidht, windowHeight, TRUE);
}