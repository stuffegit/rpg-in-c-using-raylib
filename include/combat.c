#include "combat.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void timer_start(CombatTimer* timer, double timelife) {
  timer->timestart = GetTime();
  timer->timelife = timelife;
}

bool timer_done(CombatTimer* timer) {
  return GetTime() - timer->timestart >= timer->timelife;
}

double timer_elapsed(CombatTimer* timer) {
  return GetTime() - timer->timestart;
}

void combat_printdebuginfo(Player* player, Font* nfont) {
  DrawTextEx(
      *nfont,
      TextFormat(
          "Nam: %s\nGen: %c\nRce: %s\nRol: %s\nBgd: %s\nLyr: %s\n\nBdy: %d\nDex: %d\nFtg: %d\n"
          "Con: %d\n\nH|P: %d/%d\nM|P: %d/%d\nAtk: %d\nPwr: %d\nDef: %d\nDur: %d\n",
          player->name, player->gender, player->origin.origin_id, player->role.role_id,
          player->background, player->layer, player->body, player->dexterity, player->fatigue,
          player->connection, player->hp, player->hpmax, player->mp, player->mpmax, player->attack,
          player->power, player->defense, player->durability),
      (Vector2){0, 0}, 32, 1, WHITE);
}

void combat_drawboxbackground(GameContext* ctx, int width, int height) {
  DrawRectangle(
      0, 0, (int)ctx->setting.resolution.x, (int)ctx->setting.resolution.y,
      CLITERAL(Color){15, 59, 58, 255});
  combat_printdebuginfo(&ctx->player, &ctx->setting.nfont);
}

void combat_init(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars) {
  ctx->combat.menu.background.height = 300;
  ctx->combat.menu.background.width = ctx->setting.resolution.x;
  ctx->combat.menu.background.y = ctx->setting.resolution.y - ctx->combat.menu.background.height;
  ctx->combat.menu.background.x = 0;
  background->x = (float)ctx->combat.menu.background.x;
  background->y = (float)ctx->combat.menu.background.y;
  background->width = (float)ctx->combat.menu.background.width;
  background->height = (float)ctx->combat.menu.background.height;

  ctx->combat.menu.selection.x = ctx->combat.menu.background.x + 5;
  ctx->combat.menu.selection.y = ctx->combat.menu.background.y + 5;
  ctx->combat.menu.selection.width = 300;
  ctx->combat.menu.selection.height = ctx->combat.menu.background.height - 10;
  selection->x = (float)ctx->combat.menu.selection.x;
  selection->y = (float)ctx->combat.menu.selection.y;
  selection->width = (float)ctx->combat.menu.selection.width;
  selection->height = (float)ctx->combat.menu.selection.height;

  ctx->combat.menu.initiativebars.x =
      ctx->combat.menu.selection.x + ctx->combat.menu.selection.width + 5;
  ctx->combat.menu.initiativebars.y = ctx->combat.menu.background.y + 5;
  ctx->combat.menu.initiativebars.width = ctx->combat.menu.selection.width + 800;
  ctx->combat.menu.initiativebars.height = ctx->combat.menu.background.height - 10;
  initiativebars->x = (float)ctx->combat.menu.initiativebars.x;
  initiativebars->y = (float)ctx->combat.menu.initiativebars.y;
  initiativebars->width = (float)ctx->combat.menu.initiativebars.width;
  initiativebars->height = (float)ctx->combat.menu.initiativebars.height;

  ctx->combat.menu.statusbars.x =
      ctx->combat.menu.initiativebars.x + ctx->combat.menu.initiativebars.width + 5;
  ctx->combat.menu.statusbars.y = ctx->combat.menu.background.y + 5;
  ctx->combat.menu.statusbars.width = 500;
  ctx->combat.menu.statusbars.height = ctx->combat.menu.background.height - 10;
  statusbars->x = (float)ctx->combat.menu.statusbars.x;
  statusbars->y = (float)ctx->combat.menu.statusbars.y;
  statusbars->width = (float)ctx->combat.menu.statusbars.width;
  statusbars->height = (float)ctx->combat.menu.statusbars.height;

  for (int i = 0; i < 4; i++) {
    ctx->combat.menu.choices[i].x = selection->x + 5.0f;
    ctx->combat.menu.choices[i].y = selection->y + 5.0f + (float)i * 71.0f;
    ctx->combat.menu.choices[i].width = selection->width - 10.0f;
    ctx->combat.menu.choices[i].height = 66.0f;
  }
  player_updatestats(&ctx->player);
  ctx->combat.state = COMBAT_PLAYERTURNSTART;
}

void combat_update(GameContext* ctx) {
  player_updatestats(&ctx->player);
}

static void combat_draw(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars) {
  combat_drawboxbackground(ctx, ctx->setting.resolution.x, ctx->setting.resolution.y);

  // Menu background
  DrawRectangleRec(*background, CLITERAL(Color){0, 0, 0, 100});

  // Drawing individual menus
  if (ctx->combat.state == COMBAT_PLAYERTURNSTART) {
    combat_drawmenu_selection(ctx, background, selection);
  }
  combat_drawmenu_initiativebars(ctx, background, initiativebars);
  combat_drawmenu_statusbars(ctx, background, statusbars);
}

void combat_drawmenu_selection(GameContext* ctx, Rectangle* background, Rectangle* selection) {
  DrawRectangleRec(*selection, CLITERAL(Color){0, 0, 0, 100});
  for (int i = 0; i < 4; i++) {
    DrawRectangleRec(ctx->combat.menu.choices[i], CLITERAL(Color){255, 255, 255, 50});
    Vector2 textoffset = MeasureTextEx(ctx->setting.nfont, ctx->player.combat_options[i], 32, 1);
    DrawTextEx(
        ctx->setting.nfont, ctx->player.combat_options[i],
        (Vector2){selection->x + (selection->width / 2) - textoffset.x / 2,
                  selection->y + (70 * i) + 25},
        32, 1, (ctx->player.combat_options_enabled[i] == 1) ? WHITE : GRAY);
  }
}

void combat_drawmenu_initiativebars(
    GameContext* ctx, Rectangle* background, Rectangle* initiativebars) {
  DrawRectangleRec(*initiativebars, CLITERAL(Color){0, 0, 0, 100});
}

void combat_drawmenu_statusbars(GameContext* ctx, Rectangle* background, Rectangle* statusbars) {
  DrawRectangleRec(*statusbars, CLITERAL(Color){0, 0, 0, 100});
  const char* statusbartext = TextFormat(
      "%s \nhp%d/%d \n\nmp%d/%d", ctx->player.name, ctx->player.hp, ctx->player.hpmax,
      ctx->player.mp, ctx->player.mpmax);
  Vector2 textpos = (Vector2){statusbars->x + (statusbars->width / 2) - 200, statusbars->y + 25};
  float hpbarlength =
      (((statusbars->width / 2.0f) + 90.0f) / (float)ctx->player.hpmax) * (float)ctx->player.hp;
  float mpbarlength =
      (((statusbars->width / 2.0f) + 90.0f) / (float)ctx->player.mpmax) * (float)ctx->player.mp;
  DrawTextEx(ctx->setting.nfont, statusbartext, textpos, 32, 1, WHITE);
  DrawRectangle(
      statusbars->x + (statusbars->width / 2) - 200, statusbars->y + 95,
      (statusbars->width / 2) + 100, 25, CLITERAL(Color){255, 5, 5, 255});
  DrawRectangle(
      5 + statusbars->x + (statusbars->width / 2) - 200, statusbars->y + 100, (int)hpbarlength, 15,
      CLITERAL(Color){255, 255, 255, 255});
  DrawRectangle(
      statusbars->x + (statusbars->width / 2) - 200, statusbars->y + 160,
      (statusbars->width / 2) + 100, 25, CLITERAL(Color){255, 5, 5, 255});
  DrawRectangle(
      5 + statusbars->x + (statusbars->width / 2) - 200, statusbars->y + 165, (int)mpbarlength, 15,
      CLITERAL(Color){255, 255, 255, 255});
}

void combat_player_damage(GameContext* ctx, Player* player, Enemy* enemy) {
  printf("\n-- PLAYER TURN START --");
  printf(
      "\n%s attacks: %d-%d vs %s's defense %d -> ", player->name, player->level, player->attack,
      enemy->name, enemy->defense);
  int atkroll = player->level + rand() % player->attack;
  if (atkroll >= enemy->defense || atkroll == player->attack) {
    printf("%d hits!\n", atkroll);
    int dmgdone = 0;
    int dmgtaken = 0;
    printf("%s rolls damage %dd%d -> ", player->name, player->level, player->power);
    dmgdone = 1 + rand() % player->power;
    printf("%d damage.\n", dmgdone);
    if (dmgdone > enemy->durability) {
      dmgtaken = dmgdone - enemy->durability;
      printf(
          "%s takes %d damage reducing their hp from %d to %d.\n", enemy->name, dmgtaken, enemy->hp,
          enemy->hp - dmgtaken);
      enemy->hp -= dmgtaken;
    } else {
      printf("%s takes no damage.\n", enemy->name);
    }
  } else {
    printf("%d miss..\n", atkroll);
  }
  timer_start(&ctx->combat.timer, 2.0);
  printf("-- PLAYER TURN END --\n");
}

void combat_enemy_damage(GameContext* ctx, Enemy* enemy, Player* player) {
  printf("\n-- ENEMY TURN START --\n");
  printf(
      "%s attacks %d-%d vs %s's defense %d -> ", enemy->name, enemy->level, enemy->attack,
      player->name, player->defense);
  int atkroll = enemy->level + rand() % (enemy->attack);
  if (atkroll >= player->defense) {
    printf("%d hits!\n", atkroll);
    int dmgdone = 0;
    int dmgtaken = 0;
    printf(
        "%s rolls damage %d-%d vs %s's durability %d -> ", enemy->name, enemy->level, enemy->power,
        player->name, player->durability);
    dmgdone = enemy->level + rand() % enemy->power;
    printf("%d damage.\n", dmgdone);
    if (dmgdone > player->durability) {
      dmgtaken = dmgdone - player->durability;
      printf(
          "%s takes %d damage reducing their hp from %d to %d.\n", player->name, dmgtaken,
          player->hp, player->hp - dmgtaken);
      player->hp -= dmgtaken;
    } else {
      printf("%s takes no damage.\n", player->name);
    }
  } else {
    printf("%d miss..\n", atkroll);
  }
  timer_start(&ctx->combat.timer, 2.0);
  printf("-- ENEMY TURN END --\n");
}

void combat_handle(GameContext* ctx) {
  static Rectangle combatmenu_background;
  static Rectangle combatmenu_selection;
  static Rectangle combatmenu_initiativebars;
  static Rectangle combatmenu_statusbars;
  switch (ctx->combat.state) {
  case COMBAT_NON:
    printf("\nERR: combat_handle() - state is COMBAT_NON.\n");
    break;
  case COMBAT_START:
    combat_init(
        ctx, &combatmenu_background, &combatmenu_selection, &combatmenu_initiativebars,
        &combatmenu_statusbars);
    break;
  case COMBAT_PLAYERTURNSTART:
    // Handle the player turn
    if (CheckCollisionPointRec(GetMousePosition(), ctx->combat.menu.choices[0]) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      combat_player_damage(ctx, &ctx->player, &ctx->enemy);
      ctx->combat.state = COMBAT_PLAYERTURNEND;
    }
    break;
  case COMBAT_PLAYERTURNEND:
    if (timer_done(&ctx->combat.timer)) {
      ctx->combat.state = COMBAT_ENEMYTURNSTART;
    }
    break;
  case COMBAT_ENEMYTURNSTART:
    // Handle the current combatants turn
    if (timer_done(&ctx->combat.timer)) {
      combat_enemy_damage(ctx, &ctx->enemy, &ctx->player);
      ctx->combat.state = COMBAT_ENEMYTURNEND;
    }
    break;
  case COMBAT_ENEMYTURNEND:
    if (timer_done(&ctx->combat.timer)) {
      ctx->combat.state = COMBAT_PLAYERTURNSTART;
    }
    break;
  case COMBAT_ABT:
    // Let the ActiveBattleTime tick down, depends on stat: initiative
    break;
  case COMBAT_END:
    // Handle XP/AP/Money/Drops
    ctx->state = STATE_MAINMENU;
    break;
  }
  combat_update(ctx);
  combat_draw(
      ctx, &combatmenu_background, &combatmenu_selection, &combatmenu_initiativebars,
      &combatmenu_statusbars);
}
