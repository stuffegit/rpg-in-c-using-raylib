#include "game.h"
#include <stdio.h>

const char* menu_strings[3] = {"Start Game", "Combat Debug", "Quit"};
Rectangle menu_item[3];

void game_mainmenu_printdebuginfo(const GameContext* ctx) {
  switch (ctx->state) {
  case 0:
    DrawText("Gamestate: QUIT", (ctx->setting.resolution.x / 2) - 100, 0, 20, WHITE);
    break;
  case 1:
    DrawText("Gamestate: MENU", (ctx->setting.resolution.x / 2) - 100, 0, 20, WHITE);
    break;
  case 2:
    DrawText("Gamestate: START", (ctx->setting.resolution.x / 2) - 100, 0, 20, WHITE);
    break;
  case 3:
    DrawText("Gamestate: COMBAT", (ctx->setting.resolution.x / 2) - 100, 0, 20, WHITE);
    break;
  }
}

void game_mainmenu_handle(GameContext* ctx) {
  // Box containing items
  DrawRectangle(
      (ctx->setting.resolution.x - 200) / 2, (ctx->setting.resolution.y - 200) / 2, 200, 200,
      CLITERAL(Color){0, 117, 44, 255});
  // Fill rect with size/pos data
  for (int i = 0; i < 3; i++) {
    menu_item[i].x =
        (float)(ctx->setting.resolution.x / 2) - (float)(MeasureText(menu_strings[i], 20) / 2);
    menu_item[i].y = (float)(ctx->setting.resolution.y / 2) + (-70 + (i * 60));
    menu_item[i].width = (float)MeasureText(menu_strings[i], 20);
    menu_item[i].height = 20;
  }
  // Actually draw items
  for (int i = 0; i < 3; i++) {
    DrawText(menu_strings[i], (int)menu_item[i].x, (int)menu_item[i].y, 20, BLACK);
  }
  if (CheckCollisionPointRec(GetMousePosition(), menu_item[2]) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ctx->state == STATE_MAINMENU) {
    ctx->state = STATE_EXIT;
  }
  if (CheckCollisionPointRec(GetMousePosition(), menu_item[1]) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ctx->state == STATE_MAINMENU) {
    // Combat debug
    ctx->player.level = 1;
    ctx->player.hp = 100;
    ctx->player.hpmax = 100;
    ctx->player.attack = 10;
    ctx->player.power = 6;
    ctx->state = STATE_COMBAT;
    ctx->combat.state = COMBAT_START;
  }
  if (CheckCollisionPointRec(GetMousePosition(), menu_item[0]) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ctx->state == STATE_MAINMENU) {
    ctx->state = STATE_CHARCREATE;
  }
}
