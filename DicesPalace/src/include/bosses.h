#pragma once
#include <string>                       // For string manipulation

// Variables and functions for boss battles in the RPG game
extern int bossHP;
extern int ronda;
extern int progress; // For big boss battles
extern int currentQuestionIndex;

bool startBossBattle();
bool fightRegularEnemy();
bool bossBattleRPG(bool (*minigame)(int, int), const std::string& bossArt, int color);
