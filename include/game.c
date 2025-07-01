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
  case STATE_DEBUG:
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
        ctx->setting.nfont, "Gamemode: EXIT", (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20},
        20, 1, WHITE);
    break;
  case 1:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: MAINMENU",
        (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20}, 20, 1, WHITE);
    break;
  case 2:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: SETTINGS",
        (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20}, 20, 1, WHITE);
    break;
  case 3:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: GAME", (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20},
        20, 1, WHITE);
    break;
  case 4:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: DEBUG",
        (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20}, 20, 1, WHITE);
    break;
  case 5:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: COMBAT",
        (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20}, 20, 1, WHITE);
    break;
  case 6:
    DrawTextEx(
        ctx->setting.nfont, "Gamemode: CHARCREATE",
        (Vector2){ctx->setting.resolution.x / 2.0f - 100, 20}, 20, 1, WHITE);
    break;
  }
}

void game_handle(GameContext* ctx) {

  // Overlap enemy square
  if (ctx->player.playerpos.x == 1 && ctx->player.playerpos.y == 1) {
    strcpy(ctx->enemy.name, "Level1");
    ctx->enemy.level = 1;
    ctx->enemy.attack = 1;
    ctx->enemy.power = 1;
    ctx->enemy.defense = 1;
    ctx->enemy.durability = 1;
    ctx->enemy.hpmax = 10;
    ctx->enemy.hp = ctx->enemy.hpmax;
    ctx->enemy.mpmax = 10;
    ctx->enemy.mp = ctx->enemy.mpmax;

    ctx->enemy.xp = 1;
    ctx->enemy.ap = 1;
    ctx->enemy.moneydrop = 5;

    ctx->state = STATE_COMBAT;
    ctx->combat.state = COMBAT_START;
  } else if (ctx->player.playerpos.x == 2 && ctx->player.playerpos.y == 1) {
    strcpy(ctx->enemy.name, "Level2");
    ctx->enemy.level = 2;
    ctx->enemy.attack = 3;
    ctx->enemy.power = 3;
    ctx->enemy.defense = 3;
    ctx->enemy.durability = 3;
    ctx->enemy.hpmax = 25;
    ctx->enemy.hp = ctx->enemy.hpmax;
    ctx->enemy.mpmax = 25;
    ctx->enemy.mp = ctx->enemy.mpmax;

    ctx->enemy.xp = 2;
    ctx->enemy.ap = 2;
    ctx->enemy.moneydrop = 10;

    ctx->state = STATE_COMBAT;
    ctx->combat.state = COMBAT_START;
  } else if (ctx->player.playerpos.x == 3 && ctx->player.playerpos.y == 1) {
    strcpy(ctx->enemy.name, "Level3");
    ctx->enemy.level = 3;
    ctx->enemy.attack = 5;
    ctx->enemy.power = 5;
    ctx->enemy.defense = 5;
    ctx->enemy.durability = 5;
    ctx->enemy.hpmax = 50;
    ctx->enemy.hp = ctx->enemy.hpmax;
    ctx->enemy.mpmax = 50;
    ctx->enemy.mp = ctx->enemy.mpmax;

    ctx->enemy.xp = 5;
    ctx->enemy.ap = 5;
    ctx->enemy.moneydrop = 15;

    ctx->state = STATE_COMBAT;
    ctx->combat.state = COMBAT_START;
  } else if (ctx->player.playerpos.x == 4 && ctx->player.playerpos.y == 1) {
    strcpy(ctx->enemy.name, "Level4");
    ctx->enemy.level = 4;
    ctx->enemy.attack = 10;
    ctx->enemy.power = 10;
    ctx->enemy.defense = 10;
    ctx->enemy.durability = 10;
    ctx->enemy.hpmax = 150;
    ctx->enemy.hp = ctx->enemy.hpmax;
    ctx->enemy.mpmax = 150;
    ctx->enemy.mp = ctx->enemy.mpmax;

    ctx->enemy.xp = 10;
    ctx->enemy.ap = 10;
    ctx->enemy.moneydrop = 50;

    ctx->state = STATE_COMBAT;
    ctx->combat.state = COMBAT_START;
  }

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
