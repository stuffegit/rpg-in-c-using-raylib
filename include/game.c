#include "game.h"
#include "charcreate.h"
#include "player.h"
#include "enemy.h"
#include "combat.h"
#include "map.h"
#include "stdio.h"

void game_init(GameContext* ctx) {
  InitAudioDevice();
  player_init(&ctx->player);
  enemy_init(&ctx->enemy);
  game_setting_init(&ctx->setting);
  ctx->state = STATE_MAINMENU;
  ctx->combat.state = COMBAT_NON;
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(ctx->setting.resolution.x, ctx->setting.resolution.y, "videogame playing for fun");
  game_setting_fontinit(&ctx->setting);
  SetTargetFPS(60);
  ctx->player.playerpos = (Vector2){2, 2};
}

void game_exit(GameContext* ctx) {
  CloseAudioDevice();
}

void game_update(GameContext* ctx) {
  switch (ctx->state) {
  case STATE_MAINMENU:
    game_mainmenu_handle(ctx);
    break;
  case STATE_CHARCREATE:
    charcreate_handle(ctx);
    break;
  case STATE_GAME:
    game_handle(ctx);
    break;
  case STATE_COMBAT:
    combat_handle(ctx);
    break;
  case STATE_SETTINGS:
    game_setting_handle(&ctx->setting);
    break;
  }
}

void game_draw(GameContext* ctx) {
  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}

void game_printdebuginfo(GameContext* ctx) {
  switch (ctx->state) {
  case 0:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: CC", (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20},
        20, 1, WHITE);
    break;
  case 1:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: EXIT", (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20},
        20, 1, WHITE);
    break;
  case 2:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: PLAY", (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20},
        20, 1, WHITE);
    break;
  }
}

void game_handle(GameContext* ctx) {
  if (IsKeyPressed(KEY_W)) {
    printf("Player pos b4: %f : %f\n", ctx->player.playerpos.y, ctx->player.playerpos.x);
    printf("Enemy pos b4: %f : %f\n", ctx->player.playerpos.y, ctx->player.playerpos.x);
    if (ctx->player.playerpos.y >= 2) {
      ctx->player.playerpos.y -= 1.0f;
    }
  }
  if (IsKeyPressed(KEY_S)) {
    printf("Player pos b4: %f : %f\n", ctx->player.playerpos.y, ctx->player.playerpos.x);
    if (ctx->player.playerpos.y <= MAPHEIGHT - 3) {
      ctx->player.playerpos.y += 1.0f;
    }
  }
  if (IsKeyPressed(KEY_A)) {
    printf("Player pos b4: %f : %f\n", ctx->player.playerpos.y, ctx->player.playerpos.x);
    if (ctx->player.playerpos.x >= 2) {
      ctx->player.playerpos.x -= 1.0f;
    }
  }
  if (IsKeyPressed(KEY_D)) {
    printf("Player pos b4: %f : %f\n", ctx->player.playerpos.y, ctx->player.playerpos.x);
    if (ctx->player.playerpos.x <= MAPWIDTH - 3) {
      ctx->player.playerpos.x += 1.0f;
    }
  }
  DrawRectangle(0, 0, ctx->setting.resolution.x, ctx->setting.resolution.y, BACKGROUNDCOLOR);
  map_testdraw(ctx);
  game_printdebuginfo(ctx);
}
