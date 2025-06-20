#ifndef CHARCREATE_H
#define CHARCREATE_H

#include "game.h"
#include <raylib.h>

void charcreate_printdebuginfo(GameContext* ctx);

void charcreate_drawbox(Rectangle box, const char* label, bool selected);

void charcreate_capitalizeplayername(player_t* player);

void charcreate_handle(GameContext* ctx);

#endif // CHARCREATE_H
