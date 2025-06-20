#ifndef PLAYER_H
#define PLAYER_H

#include "race.h"
#include "role.h"

#define PLAYER_MAXNAMELEN 15
#define PLAYER_MAXIDLEN 4

typedef struct {
  // System identifiers
  int level;
  char name[PLAYER_MAXNAMELEN + 1];
  char gender;
  race_t race;
  role_t role;
  char background[PLAYER_MAXIDLEN + 1];
  char layer[PLAYER_MAXIDLEN + 1];

  // Primary stats
  int body;
  int dexterity;
  int fatigue;
  int connection;

  // Secondary stats
  int hp;
  int mp;
  int attack;
  int power;
  int defense;
  int durability;
} player_t;

void player_init(player_t* player);

void player_updatestats(player_t* player);

#endif // PLAYER_H
