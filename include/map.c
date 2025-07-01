#include "map.h"
#include <raylib.h>
#include <stdio.h>

// clang-format off
char debugtestmap_grid[MAPHEIGHT][MAPWIDTH] = {
  "####################",
  "#1234..............#", 
  "#..................#",
  "#..................#", 
  "#..................#",
  "#..................#",
  "#..................#", 
  "#..................#",
  "#..................#",
  "#..................#", 
  "#..................#",
  "#..................#",
  "#..................#", 
  "#..................#",
  "####################"};
// clang-format on

void map_testdraw(GameContext* ctx) {
  Vector2 mapsize = (Vector2){MAPWIDTH * TILESIZE, MAPHEIGHT * TILESIZE};
  Color tilecolor = RED;
  int enemy = 0;
  for (int i = 0; i < MAPHEIGHT; i++) {
    for (int j = 0; j < MAPWIDTH; j++) {
      if (debugtestmap_grid[i][j] == '#') {
        tilecolor = DARKGRAY;
      } else if (debugtestmap_grid[i][j] == '.') {
        tilecolor = GREEN;
      } else if (debugtestmap_grid[i][j] == '^') {
        tilecolor = BROWN;
      } else if (debugtestmap_grid[i][j] == 't') {
        tilecolor = DARKGREEN;
      } else if (debugtestmap_grid[i][j] == '~') {
        tilecolor = BLUE;
      } else if (debugtestmap_grid[i][j] == '@') {
        tilecolor = GREEN;
      } else if (debugtestmap_grid[i][j] == '1') {
        tilecolor = RAYWHITE;
        enemy = 1;
      } else if (debugtestmap_grid[i][j] == '2') {
        tilecolor = RAYWHITE;
        enemy = 2;
      } else if (debugtestmap_grid[i][j] == '3') {
        tilecolor = RAYWHITE;
        enemy = 3;
      } else if (debugtestmap_grid[i][j] == '4') {
        tilecolor = RAYWHITE;
        enemy = 4;
      }
      DrawRectangle(
          j * OFFSET + (((ctx->setting.resolution.x / 2) - ((int)mapsize.x / 2)) + j * TILESIZE),
          i * OFFSET + (((ctx->setting.resolution.y / 2) - ((int)mapsize.y / 2)) + i * TILESIZE),
          TILESIZE, TILESIZE, tilecolor);
      if (i == ctx->player.playerpos.y && j == ctx->player.playerpos.x) {
        DrawTextEx(
            ctx->setting.nfont, "P",
            (Vector2){((((((float)ctx->setting.resolution.x / 2.0f) - (mapsize.x / 2.0f)) +
                         j * TILESIZE)) +
                       ((float)TILESIZE * 0.25f)) +
                          1.0f * (float)j,
                      ((((((float)ctx->setting.resolution.y / 2.0f) - (mapsize.y / 2.0f)) +
                         i * TILESIZE)) +
                       ((float)TILESIZE * 0.2f)) +
                          1.0f * (float)i},
            TILESIZE, 1, BLACK);
      }
    }
  }
}
