#ifndef CHARCREATE_H
#define CHARCREATE_H

#include "game.h"
#include <raylib.h>

void charcreate_printdebuginfo(player_t* player, Font* nfont);

void charcreate_drawbox(Rectangle* box, GameContext* ctx, const char* label, bool selected);

void charcreate_drawboxbackground(GameContext* ctx, char* title, int width, int height);

void charcreate_drawconfirmbox(Rectangle* box, GameContext* ctx);

void charcreate_capitalizeplayername(player_t* player);

void charcreate_handle(GameContext* ctx);

#endif // CHARCREATE_H
