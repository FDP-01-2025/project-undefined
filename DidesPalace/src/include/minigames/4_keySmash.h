#pragma once

const int WIDTH = 40; // Width of the game area
const int HEIGHT = 20; // Height of the game area
const int NUM_KEYS = 5; // Simultaneous active letters

// Structure to represent a letter
struct Key{
    // Stores the letter
    char letter;
    // Coordinates of the letter in the game area
    int x, y;
    // Indicates if the letter is active
    bool active;
};

// Functions to implement
bool playKeySmash(int posX = 0, int posY = 0);
// Function that generates a random letter between 'A' and 'Z'
char getRandomKey(); 
// Function that draws a frame around the game area
void drawFrame(int posX, int posY);