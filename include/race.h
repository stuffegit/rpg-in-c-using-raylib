#ifndef RACE_H
#define RACE_H

typedef struct {
  char race_id[10];
  int body_bonus;
  int dexterity_bonus;
  int layer_bonus;
  int connection_bonus;

  int hp_bonus;
  int mp_bonus;
  int attack_bonus;
  int power_bonus;
  int defense_bonus;
  int durability_bonus;
} race_t;
race_t race;

race_t race_select(int choice);

#endif // RACE_H
