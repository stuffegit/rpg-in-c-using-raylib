#include "enemy.h"
#include "string.h"

void enemy_init(Enemy* enemy) {
  enemy->level = 0;
  strcpy(enemy->name, "Spökmonster");

  enemy->body = 0;
  enemy->dexterity = 0;
  enemy->fatigue = 0;
  enemy->connection = 0;

  enemy->hp = 0;
  enemy->hpmax = 0;
  enemy->mp = 0;
  enemy->mpmax = 0;
  enemy->attack = 0;
  enemy->power = 0;
  enemy->defense = 0;
  enemy->durability = 0;
}

void enemy_updatestats(Enemy* enemy) {
  enemy->body = 0;
  enemy->dexterity = 0;
  enemy->fatigue = 0;
  enemy->connection = 0;

  enemy->hp = 0;
  enemy->mp = 0;
  enemy->attack = 0;
  enemy->power = 0;
  enemy->defense = 0;
  enemy->durability = 0;
}
