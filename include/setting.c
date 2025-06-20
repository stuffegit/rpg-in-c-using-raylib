#include "setting.h"
#include <stdio.h>

void setting_init(Settings* setting) {
  setting->resolution = (iVec2){1920, 1080};
}

void setting_fontinit(Settings* setting) {
  setting->nfont = LoadFontEx("resources/fonts/alagard.ttf", 32, 0, 250);
  if (setting->nfont.texture.id == 0) {
    printf("\nayo font loading is fkd\n");
  }
}

void setting_handle(Settings* setting) {
  ;
}
