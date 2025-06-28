#include "player.h"
#include <string.h>

void player_test_init(Player* player) {
  player->level = 1;
  strcpy(player->name, "TestTage");
  player->gender = 'M';
  strcpy(player->role.role_id, "Burglar");
  strcpy(player->origin.origin_id, "Alf");
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

void player_init(Player* player) {
  player->level = 1;
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
  player->body = (player->level * 1) + player->origin.body_bonus + player->role.body_bonus;
  player->dexterity =
      (player->level * 1) + player->origin.dexterity_bonus + player->role.dexterity_bonus;
  player->fatigue = (player->level * 1) + player->origin.fatigue_bonus + player->role.fatigue_bonus;
  player->connection =
      (player->level * 1) + player->origin.connection_bonus + player->role.connection_bonus;

  player->hpmax = ((player->body * 2) + (player->fatigue * 3)) / 2;
  player->mpmax = ((player->connection * 2) + (player->fatigue * 1)) / 2;
  player->attack = ((player->dexterity * 2) + (player->body * 1)) / 3;
  player->power = ((player->dexterity * 1) + (player->body * 3)) / 10;
  player->defense = ((player->body * 2) + (player->dexterity * 3)) / 6;
  player->durability = ((player->body * 5) + (player->dexterity * 1)) / 10;
}
