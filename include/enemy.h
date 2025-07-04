#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

#define ENEMY_MAXNAMELEN 15
#define ENEMY_MAXIDLEN 15

typedef struct {
  // System identifiers
  int level;
  char name[ENEMY_MAXNAMELEN + 1];
  char origin[ENEMY_MAXIDLEN + 1];

  // Secondary stats
  int hp;
  int hpmax;
  int mp;
  int mpmax;
  int attack;
  int power;
  int defense;
  int durability;

  // Enemy specific
  int moneydrop;
  int xp;
  int ap;
} Enemy;

void enemy_init(Enemy* enemy);

void enemy_load_from_json(Enemy* enemy, char* enemybp);

#endif // PLAYER_H
