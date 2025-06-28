#ifndef origin_H
#define origin_H

typedef struct {
  char origin_id[10];
  int body_bonus;
  int dexterity_bonus;
  int fatigue_bonus;
  int connection_bonus;
} origin_t;
origin_t origin;

origin_t origin_select(int choice);

#endif // origin_H
