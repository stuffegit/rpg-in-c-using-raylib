#include "player.h"
#include "game.h"

void player_init(player_t* player) {
  player->level = 0;

  player->body = 0;
  player->dexterity = 0;
  player->fatigue = 0;
  player->connection = 0;

  player->hp = 0;
  player->mp = 0;
  player->attack = 0;
  player->power = 0;
  player->defense = 0;
  player->durability = 0;
}

void player_updatestats(player_t* player) {
  player->body = 0;
  player->dexterity = 0;
  player->fatigue = 0;
  player->connection = 0;

  player->hp = 0;
  player->mp = 0;
  player->attack = 0;
  player->power = 0;
  player->defense = 0;
  player->durability = 0;
}
