#include "combat.h"

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
  ctx->combat.menu.initiativebars.width = ctx->combat.menu.background.width + 800 - 20;
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
}

void combat_update(GameContext* ctx) {
  ; // i guess numbers and shit go here
}

static void combat_draw(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars) {
  combat_drawmenu(ctx, background, selection, initiativebars, statusbars);
}

void combat_drawmenu(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars) {
  // Window background
  combat_drawboxbackground(ctx, ctx->setting.resolution.x, ctx->setting.resolution.y);

  // Menu background
  DrawRectangleRec(*background, CLITERAL(Color){0, 0, 0, 100});

  // Drawing individual menus
  combat_drawmenu_selection(ctx, background, selection);
  combat_drawmenu_initiativebars(ctx, background, initiativebars);
  combat_drawmenu_statusbars(ctx, background, statusbars);
}

void combat_drawmenu_selection(GameContext* ctx, Rectangle* background, Rectangle* selection) {
  DrawRectangleRec(*selection, CLITERAL(Color){0, 0, 0, 100});
  for (int i = 0; i < 4; i++) {
    DrawRectangle(
        (int)selection->x + 5, ((int)selection->y + 5) + i * 71, (int)selection->width - 10, 66,
        CLITERAL(Color){255, 255, 255, 50});
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

void combat_handle(GameContext* ctx) {
  // clang-format off
  static Rectangle combatmenu_background;
  static Rectangle combatmenu_selection;
  static Rectangle combatmenu_initiativebars;
  static Rectangle combatmenu_statusbars;
  combat_init(ctx, 
    &combatmenu_background, 
    &combatmenu_selection, 
    &combatmenu_initiativebars,
    &combatmenu_statusbars);
  combat_update(ctx);
  combat_draw(ctx, 
    &combatmenu_background, 
    &combatmenu_selection, 
    &combatmenu_initiativebars,
    &combatmenu_statusbars);
  // clang-format on
}
