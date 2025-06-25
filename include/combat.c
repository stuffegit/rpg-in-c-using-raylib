#include "combat.h"
#include "stdio.h"
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
          player->name, player->gender, player->race.race_id, player->role.role_id,
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
    ctx->combat.menu.choices[i].x = (int)selection->x + 5;
    ctx->combat.menu.choices[i].y = ((int)selection->y + 5) + i * 71;
    ctx->combat.menu.choices[i].width = (int)selection->width - 10;
    ctx->combat.menu.choices[i].height = 66;
  }

  ctx->combat.state = COMBAT_PLAYERTURNSTART;
}

void combat_update(GameContext* ctx) {
  ; // i guess numbers and shit go here
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
      "%s\nHP: %d/%d\nMP: %d/%d", ctx->player.name, ctx->player.hp, ctx->player.hpmax,
      ctx->player.mp, ctx->player.mpmax);
  Vector2 textoffset = MeasureTextEx(ctx->setting.nfont, statusbartext, 32, 1);
  Vector2 textpos =
      (Vector2){statusbars->x + (statusbars->width / 2) - textoffset.x / 2, statusbars->y + 25};
  DrawTextEx(ctx->setting.nfont, statusbartext, textpos, 32, 1, WHITE);
}

void combat_player_damage(GameContext* ctx, Player* player, Enemy* enemy) {
  if (1 + ((rand() % (player->attack + 2)) + player->attack - 2) >= 10) {
    int dmgdone = 0;
    int dmgtaken = 0;
    dmgdone = 1 + rand() % player->power;
    dmgtaken = dmgdone - enemy->durability;
    printf("\nPlayer rolls %dd%d.\n", player->level, player->attack);
    printf("It lands on %d.\n", dmgdone);
    printf(
        "Enemy %s takes %d damage reducing their hp from %d to %d.\n", enemy->name, dmgtaken,
        enemy->hp, enemy->hp - dmgtaken);
    enemy->hp -= dmgdone;
    timer_start(&ctx->combat.timer, 2.0);
  }
}

void combat_enemy_damage(GameContext* ctx, Enemy* enemy, Player* player) {
  if (1 + ((rand() % (enemy->attack + 2)) + enemy->attack - 2) >= 10) {
    int dmgdone = 0;
    int dmgtaken = 0;
    dmgdone = 1 + rand() % enemy->power;
    dmgtaken = dmgdone - player->durability;
    printf("\nEnemy rolls %dd%d.\n", enemy->level, enemy->attack);
    printf("It lands on %d.\n", dmgdone);
    printf(
        "Player %s takes %d damage reducing their hp from %d to %d.\n", player->name, dmgtaken,
        player->hp, player->hp - dmgtaken);
    player->hp -= dmgdone;
    timer_start(&ctx->combat.timer, 2.0);
  }
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
