#ifndef ROLE_H
#define ROLE_H

typedef struct {
  char role_id[13];
  int body_bonus;
  int dexterity_bonus;
  int fatigue_bonus;
  int connection_bonus;
} role_t;
role_t role;

role_t role_select(int choice);

#endif // ROLE_H
