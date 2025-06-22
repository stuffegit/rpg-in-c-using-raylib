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

void combat_init(GameContext* ctx) {
  ctx->combatmenu.height = 300;
  ctx->combatmenu.width = ctx->setting.resolution.x;
  ctx->combatmenu.y = ctx->setting.resolution.y - ctx->combatmenu.height;
  ctx->combatmenu.x = 0;
}
void combat_update(GameContext* ctx) {
  ;
}

void combat_drawmenu(
    GameContext* ctx, Rectangle* combatmenu_background, Rectangle* combatmenu_selection,
    Rectangle* combatmenu_initiativebars, Rectangle* combatmenu_statusbars) {
  // Window background
  combat_drawboxbackground(ctx, ctx->setting.resolution.x, ctx->setting.resolution.y);

  // Menu background
  DrawRectangleRec(*combatmenu_background, CLITERAL(Color){0, 0, 0, 100});

  // Drawing individual menus
  combat_drawmenu_selection(ctx, combatmenu_background, combatmenu_selection);
  combat_drawmenu_initiativebars(ctx, combatmenu_background, combatmenu_initiativebars);
  combat_drawmenu_statusbars(ctx, combatmenu_background, combatmenu_statusbars);
}

void combat_drawmenu_selection(
    GameContext* ctx, Rectangle* combatmenu_background, Rectangle* combatmenu_selection) {
  DrawRectangleRec(*combatmenu_selection, CLITERAL(Color){0, 0, 0, 100});
  for (int i = 0; i < 4; i++) {
    DrawRectangle(
        combatmenu_selection->x + 5, (combatmenu_selection->y + 5) + i * 71,
        combatmenu_selection->width - 10, 66, CLITERAL(Color){255, 255, 255, 50});
    Vector2 textoffset = MeasureTextEx(ctx->setting.nfont, ctx->player.combat_options[i], 32, 1);
    DrawTextEx(
        ctx->setting.nfont, ctx->player.combat_options[i],
        (Vector2){combatmenu_selection->x + (combatmenu_selection->width / 2) - textoffset.x / 2,
                  combatmenu_selection->y + (70 * i) + 25},
        32, 1, (ctx->player.combat_options_enabled[i] == 1) ? WHITE : GRAY);
  }
}

void combat_drawmenu_initiativebars(
    GameContext* ctx, Rectangle* combatmenu_background, Rectangle* combatmenu_initiativebars) {
  DrawRectangleRec(*combatmenu_initiativebars, CLITERAL(Color){0, 0, 0, 100});
}

void combat_drawmenu_statusbars(
    GameContext* ctx, Rectangle* combatmenu_background, Rectangle* combatmenu_statusbars) {
  DrawRectangleRec(*combatmenu_statusbars, CLITERAL(Color){0, 0, 0, 100});
  char* statusbars = TextFormat(
      "%s\nHP: %d/%d\nMP: %d/%d", ctx->player.name, ctx->player.hp, ctx->player.hpmax,
      ctx->player.mp, ctx->player.mpmax);
  Vector2 textoffset = MeasureTextEx(ctx->setting.nfont, statusbars, 32, 1);
  Vector2 textpos =
      (Vector2){combatmenu_statusbars->x + (combatmenu_statusbars->width / 2) - textoffset.x / 2,
                combatmenu_statusbars->y + 25};
  DrawTextEx(ctx->setting.nfont, statusbars, textpos, 32, 1, WHITE);
}

void combat_handle(GameContext* ctx) {
  combat_init(ctx);
  Rectangle combatmenu_background = {
      ctx->combatmenu.x, ctx->combatmenu.y, ctx->combatmenu.width, ctx->combatmenu.height};
  Rectangle combatmenu_selection = {
      ctx->combatmenu.x + 5, ctx->combatmenu.y + 5, 300, ctx->combatmenu.height - 10};
  Rectangle combatmenu_initiativebars = {
      combatmenu_selection.x + combatmenu_selection.width + 5, ctx->combatmenu.y + 5,
      ctx->combatmenu.width - (20 + 800), ctx->combatmenu.height - 10};
  Rectangle combatmenu_statusbars = {
      combatmenu_initiativebars.x + combatmenu_initiativebars.width + 5, ctx->combatmenu.y + 5, 500,
      ctx->combatmenu.height - 10};
  combat_update(ctx);
  combat_drawmenu(
      ctx, &combatmenu_background, &combatmenu_selection, &combatmenu_initiativebars,
      &combatmenu_statusbars);
}
