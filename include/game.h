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
  STATE_COMBAT,
  STATE_CHARCREATE,
} GameState;

typedef enum {
  COMBAT_NON,
  COMBAT_START,
  COMBAT_FIRSTTURN,
  COMBAT_ABT,
  COMBAT_TURN,
} CombatState;

typedef struct {
  int x;
  int y;
} iVec2;

typedef struct {
  float x;
  float y;
} fVec2;

typedef struct {
  iVec2 resolution;
  Font nfont;
} Settings;

typedef struct {
  int x;
  int y;
  int width;
  int height;
  int offset;
} CombatMenu;

typedef struct {
  struct {
    CombatMenu background;
    CombatMenu selection;
    CombatMenu initiativebars;
    CombatMenu statusbars;
  } menu;
  CombatState state;
} Combat;

typedef struct {
  Vector2 pos;
} Enemy;

typedef struct {
  GameState state;
  Player player;
  Enemy enemy;
  Combat combat;
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
