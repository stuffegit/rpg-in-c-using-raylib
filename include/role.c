#include "role.h"
#include <string.h>

role_t role_select(int choice) {
  switch (choice) {
  case 1:
    strcpy(role.role_id, "Grunt");
    role.body_bonus = 3;
    role.dexterity_bonus = 1;
    role.fatigue_bonus = 1;
    role.connection_bonus = 0;
    break;
  case 2:
    strcpy(role.role_id, "Theurgist");
    role.body_bonus = 0;
    role.dexterity_bonus = 2;
    role.fatigue_bonus = 2;
    role.connection_bonus = 2;
    break;
  case 3:
    strcpy(role.role_id, "Burglar");
    role.body_bonus = 1;
    role.dexterity_bonus = 3;
    role.fatigue_bonus = 1;
    role.connection_bonus = 0;
    break;
  }
  return role;
}
