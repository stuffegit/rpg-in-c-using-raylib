#ifndef PLAYER_H
#define PLAYER_H

#include "race.h"
#include "role.h"
#include <raylib.h>

#define PLAYER_MAXNAMELEN 15
#define PLAYER_MAXIDLEN 10

typedef struct {
  // System identifiers
  Vector2 playerpos;
  int level;
  char name[PLAYER_MAXNAMELEN + 1];
  char gender;
  race_t race;
  role_t role;
  char background[PLAYER_MAXIDLEN + 1];
  char layer[PLAYER_MAXIDLEN + 1];

  // Combat related
  char combat_options[4][10];
  int combat_options_enabled[4];

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
} Player;

void player_init(Player* player);

void player_updatestats(Player* player);

#endif // PLAYER_H
