#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "time.h"
#include "math.h"
#include "string.h"
#include <raylib.h>

typedef enum {
  STATE_EXIT,
  STATE_MAINMENU,
  STATE_SETTINGS,
  STATE_GAME,
  STATE_CHARCREATE,
} GameState;

typedef struct iVec2 {
  int x;
  int y;
} iVec2;

typedef struct Settings {
  iVec2 resolution;
  Font nfont;
} Settings;

typedef struct {
  GameState state;
  player_t player;
  Settings setting;
} GameContext;

void game_setting_init(Settings* setting);
void game_setting_fontinit(Settings* setting);
void game_setting_handle(Settings* setting);

void game_mainmenu_printdebuginfo(const GameContext* ctx);
void game_mainmenu_handle(GameContext* ctx);

void game_printdebuginfo(GameContext* ctx);
void game_init(GameContext* ctx);
void game_update(GameContext* ctx);
void game_draw(GameContext* ctx);
void game_handle(GameContext* ctx);
void game_exit(GameContext* ctx);

#endif // GAME_H
