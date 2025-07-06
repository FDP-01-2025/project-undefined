#pragma once

// Variables and functions for boss battles in the RPG game
extern int bossHP;
extern int ronda;

bool startBossBattle();
bool fightRegularEnemy();
void bossBattleRPG(bool (*minigame)(int, int));
