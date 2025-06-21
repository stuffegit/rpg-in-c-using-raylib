#ifndef MAP_H
#define MAP_H

#include "game.h"

#define TILESIZE 64
#define OFFSET 1
#define MAPWIDTH 20
#define MAPHEIGHT 15

char debugtestmap_grid[MAPHEIGHT][MAPWIDTH];

void map_testdraw(GameContext* ctx);

#endif // MAP_H
