#include "game.h"
#include "charcreate.h"
#include "player.h"
#include "setting.h"

void game_printdebuginfo(GameContext* ctx) {
  switch (ctx->state) {
  case 0:
    DrawText("Gamemode: CHARCREATION", (int)(ctx->setting.resolution.x / 2.0f) - 100, 20, 20,
             WHITE);
    break;
  case 1:
    DrawText("Gamemode: EXIT", (int)(ctx->setting.resolution.x / 2.0f) - 100, 20, 20, WHITE);
    break;
  case 2:
    DrawText("Gamemode: PLAY", (int)(ctx->setting.resolution.x / 2.0f) - 100, 20, 20, WHITE);
    break;
  }
}

void game_init(void) { (void)0; }

void game_handle(GameContext* ctx) {
  DrawRectangle(0, 0, (int)ctx->setting.resolution.x, (int)ctx->setting.resolution.y,
                CLITERAL(Color){15, 59, 58, 255});
  game_printdebuginfo(ctx);
}
