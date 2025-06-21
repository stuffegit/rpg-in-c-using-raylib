#include "game.h"
#include <stdio.h>

void game_setting_init(Settings* setting) {
  setting->resolution = (iVec2){1920, 1080};
}

void game_setting_fontinit(Settings* setting) {
  setting->nfont = LoadFontEx("resources/fonts/alagard.ttf", 32, 0, 250);
  if (setting->nfont.texture.id == 0) {
    printf("\nayo font loading is fkd\n");
  }
}

void game_setting_handle(Settings* setting) {
  ;
}
