#pragma once

const int WIDTH = 40; //Gameplay width
const int HEIGHT = 20; // gameplay height
const int NUM_KEYS = 5; //actives keys at the same time

//structure to represent each letter.
struct Key{
    // saves the letter
    char letter;
    //letter position in the frame
    int x, y;
    //indicates if the letter is still active
    bool active;
};

//functions implemented
bool playKeySmash(int posX = 0, int posY = 0);
// key randomizer (between a-z)
char getRandomKey(); 
// function that draws the the frame
void drawFrame(int posX, int posY);
