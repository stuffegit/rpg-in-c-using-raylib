#ifndef COMBAT_H
#define COMBAT_H

#include "game.h"

void combat_printdebuginfo(Player* player, Font* nfont);

void combat_drawboxbackground(GameContext* ctx, int width, int height);

void combat_init(GameContext* ctx);

void combat_update(GameContext* ctx);

void combat_drawmenu(
    GameContext* ctx, Rectangle* menu_background, Rectangle* menu_selection,
    Rectangle* menu_initiativebars, Rectangle* menu_statusbars);

void combat_drawmenu_selection(
    GameContext* ctx, Rectangle* menu_background, Rectangle* menu_selection);

void combat_drawmenu_initiativebars(
    GameContext* ctx, Rectangle* menu_background, Rectangle* menu_initiativebars);

void combat_drawmenu_statusbars(
    GameContext* ctx, Rectangle* menu_background, Rectangle* menu_statusbars);

void combat_handle(GameContext* ctx);

#endif // COMBAT_H
