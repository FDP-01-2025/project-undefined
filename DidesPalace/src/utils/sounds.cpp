#include <windows.h>
#include "utils/sounds.h"


//Play success sound effect
void playSuccess(){
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT("../assets/sounds/sound-success.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
};
//Play error sound effect
void playError(){
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT("../assets/sounds/sound-error.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
};
//Play the music menu
void playMenuMusic(){
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT("../assets/sounds/menu-music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
};
//Play the boss music 
void playBossMusic(){
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT("../assets/sounds/boss-music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
};
//Play the game over sound effect
void playBossGameOver(){
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT("../assets/sounds/sound-boss-gameover.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
};
//Play the level pass sound effect
void playLvlPass(){
    PlaySound(NULL, 0, 0);
    PlaySound(TEXT("../assets/sounds/sound-lvl-pass.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
};