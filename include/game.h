#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "setting.h"

typedef enum {
  STATE_EXIT,
  STATE_MAINMENU,
  STATE_SETTINGS,
  STATE_GAME,
  STATE_CHARCREATE,
} GameState;

typedef struct {
  GameState state;
  player_t player;
  Settings setting;
} GameContext;

void game_printdebuginfo(GameContext* ctx);
void game_init(void);
void game_handle(GameContext* ctx);

#endif // GAME_H
