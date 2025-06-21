#include "game.h"
#include "charcreate.h"
#include <raylib.h>

int main(void) {
  GameContext ctx = {0};
  game_init(&ctx);

  while (ctx.state != STATE_EXIT && !WindowShouldClose()) {
    game_update(&ctx);
    game_draw(&ctx);
  }
  game_exit(&ctx);
  CloseWindow();
  return 0;
}
