#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

#define ENEMY_MAXNAMELEN 15
#define ENEMY_MAXRACELEN 15

typedef struct {
  // System identifiers
  int level;
  char name[ENEMY_MAXNAMELEN + 1];
  char race[ENEMY_MAXRACELEN + 1];

  // Primary stats
  int body;
  int dexterity;
  int fatigue;
  int connection;

  // Secondary stats
  int hp;
  int hpmax;
  int mp;
  int mpmax;
  int attack;
  int power;
  int defense;
  int durability;
} Enemy;

void enemy_init(Enemy* enemy);

void enemy_updatestats(Enemy* enemy);

#endif // PLAYER_H
