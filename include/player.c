#include "player.h"

void player_init(Player* player) {
  player->level = 1;
  strcpy(player->name, "Knivkarl");
  player->gender = 'M';
  strcpy(player->role.role_id, "Burglar");
  strcpy(player->race.race_id, "Alf");
  strcpy(player->background, "Killerman");
  strcpy(player->layer, "Mentalist");
  player->playerpos = (Vector2){0, 0};
  strcpy(player->combat_options[0], "Attack");
  strcpy(player->combat_options[1], "Spell");
  strcpy(player->combat_options[2], "Item");
  strcpy(player->combat_options[3], "Escape");
  player->combat_options_enabled[0] = 1;
  player->combat_options_enabled[1] = 0;
  player->combat_options_enabled[2] = 0;
  player->combat_options_enabled[3] = 1;

  player->body = 0;
  player->dexterity = 0;
  player->fatigue = 0;
  player->connection = 0;

  player->hp = 0;
  player->hpmax = 0;
  player->mp = 0;
  player->mpmax = 0;
  player->attack = 0;
  player->power = 0;
  player->defense = 0;
  player->durability = 0;
}

void player_updatestats(Player* player) {
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
