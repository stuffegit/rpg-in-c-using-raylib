#ifndef COMBAT_H
#define COMBAT_H

#include "game.h"

void combat_printdebuginfo(Player* player, Font* nfont);

void combat_drawboxbackground(GameContext* ctx, int width, int height);

void combat_init(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars);

void combat_update(GameContext* ctx);

void combat_draw(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars);

void combat_drawmenu(
    GameContext* ctx, Rectangle* background, Rectangle* selection, Rectangle* initiativebars,
    Rectangle* statusbars);

void combat_drawmenu_selection(GameContext* ctx, Rectangle* background, Rectangle* selection);

void combat_drawmenu_initiativebars(
    GameContext* ctx, Rectangle* background, Rectangle* initiativebars);

void combat_drawmenu_statusbars(GameContext* ctx, Rectangle* background, Rectangle* statusbars);

void combat_handle(GameContext* ctx);

#endif // COMBAT_H
