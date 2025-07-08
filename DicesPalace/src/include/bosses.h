#pragma once
#include <string>                       // For string manipulation

// Variables and functions for boss battles in the RPG game
extern int bossHP;
extern int currentRound;
extern int progress; // For the progress of the game
extern int currentQuestionIndex;

bool bossBattleRPG(bool (*minigame)(int, int), const std::string& bossArt, int color);
