#include "race.h"
#include <string.h>

race_t race_select(int choice) {
  switch (choice) {
  case 1:
    strcpy(race.race_id, "Alf");
    race.body_bonus = 10;
    race.dexterity_bonus = 20;
    race.layer_bonus = 20;
    race.connection_bonus = 20;

    race.hp_bonus = 10;
    race.mp_bonus = 20;
    race.attack_bonus = 10;
    race.power_bonus = 10;
    race.defense_bonus = 0;
    race.durability_bonus = 0;
    break;
  case 2:
    strcpy(race.race_id, "Mung");
    race.body_bonus = 10;
    race.dexterity_bonus = 20;
    race.layer_bonus = 20;
    race.connection_bonus = 20;

    race.hp_bonus = 10;
    race.mp_bonus = 20;
    race.attack_bonus = 10;
    race.power_bonus = 10;
    race.defense_bonus = 0;
    race.durability_bonus = 0;
    break;
  case 3:
    strcpy(race.race_id, "Half");
    race.body_bonus = 10;
    race.dexterity_bonus = 20;
    race.layer_bonus = 20;
    race.connection_bonus = 20;

    race.hp_bonus = 10;
    race.mp_bonus = 20;
    race.attack_bonus = 10;
    race.power_bonus = 10;
    race.defense_bonus = 0;
    race.durability_bonus = 0;
    break;
  }
  return race;
}
