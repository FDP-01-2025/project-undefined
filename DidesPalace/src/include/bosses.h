#pragma once

// Variables and functions for boss battles in the RPG game
extern int bossHP;
extern int ronda;
extern int progress; // For big boss battles

bool startBossBattle();
bool fightRegularEnemy();
bool bossBattleRPG(bool (*minigame)(int, int));
