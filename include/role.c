#include "role.h"
#include <string.h>

role_t role_select(int choice) {
  switch (choice) {
  case 1:
    strcpy(role.role_id, "Grunt");
    role.body_bonus = 30;
    role.dexterity_bonus = 10;
    role.layer_bonus = 0;
    role.connection_bonus = 0;

    role.hp_bonus = 30;
    role.mp_bonus = 0;
    role.attack_bonus = 30;
    role.power_bonus = 20;
    role.defense_bonus = 20;
    role.durability_bonus = 20;
    break;
  case 2:
    strcpy(role.role_id, "Thaumaturge");
    role.body_bonus = 30;
    role.dexterity_bonus = 10;
    role.layer_bonus = 0;
    role.connection_bonus = 0;

    role.hp_bonus = 30;
    role.mp_bonus = 0;
    role.attack_bonus = 30;
    role.power_bonus = 20;
    role.defense_bonus = 20;
    role.durability_bonus = 20;
    break;
  case 3:
    strcpy(role.role_id, "Burglar");
    role.body_bonus = 30;
    role.dexterity_bonus = 10;
    role.layer_bonus = 0;
    role.connection_bonus = 0;

    role.hp_bonus = 30;
    role.mp_bonus = 0;
    role.attack_bonus = 30;
    role.power_bonus = 20;
    role.defense_bonus = 20;
    role.durability_bonus = 20;
    break;
  }
  return role;
}
