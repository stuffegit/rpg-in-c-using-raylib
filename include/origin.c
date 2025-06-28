#include "origin.h"
#include <string.h>

origin_t origin_select(int choice) {
  switch (choice) {
  case 1:
    strcpy(origin.origin_id, "Alf");
    origin.body_bonus = 1;
    origin.dexterity_bonus = 2;
    origin.fatigue_bonus = 2;
    origin.connection_bonus = 2;
    break;
  case 2:
    strcpy(origin.origin_id, "Mung");
    origin.body_bonus = 2;
    origin.dexterity_bonus = 2;
    origin.fatigue_bonus = 2;
    origin.connection_bonus = 1;
    break;
  case 3:
    strcpy(origin.origin_id, "Half");
    origin.body_bonus = 0;
    origin.dexterity_bonus = 3;
    origin.fatigue_bonus = 1;
    origin.connection_bonus = 3;
    break;
  }
  return origin;
}
