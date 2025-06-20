#include "game.h"
#include "mainmenu.h"
#include "charcreate.h"
#include "setting.h"

int main(void) {
  GameContext ctx = {0};
  player_init(&ctx.player);
  setting_init(&ctx.setting);
  ctx.state = STATE_MAINMENU;
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(ctx.setting.resolution.x, ctx.setting.resolution.y, "videogame playing for fun");
  SetTargetFPS(144);

  if (!IsWindowReady()) {
    ctx.state = STATE_EXIT; // Imagine using errorcodes
  }
  while (ctx.state != STATE_EXIT) {
    switch (ctx.state) {
    case STATE_MAINMENU:
      mainmenu_handle(&ctx);
      break;
    case STATE_CHARCREATE:
      charcreate_handle(&ctx);
      break;
    case STATE_GAME:
      game_handle(&ctx);
      break;
    case STATE_SETTINGS:
      setting_handle(&ctx.setting);
      break;
    }
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
