#ifndef SETTING_H
#define SETTING_H

#include <raylib.h>

typedef struct iVec2 {
  int x;
  int y;
} iVec2;

typedef struct Settings {
  iVec2 resolution;
} Settings;

void setting_init(Settings* setting);
void setting_handle(Settings* setting);

#endif // SETTING_H
