#include "charcreate.h"
#include "player.h"
#include "role.h"
#include "race.h"
#include "setting.h"
#include <ctype.h>
#include <string.h>

bool player_initialized = false;
int ccstep = 0;
char name[PLAYER_MAXNAMELEN + 1] = "\0";
int letter_count = 0;
int gender_selected = 0;
int race_selected = 0;
int role_selected = 0;
int background_selected = 0;
int layer_selected = 0;

void charcreate_printdebuginfo(GameContext* ctx) {
  DrawText(TextFormat("Nam: %s", ctx->player.name), 0, 1, 20, WHITE);
  DrawText(TextFormat("Gen: %c", ctx->player.gender), 0, 22, 20, WHITE);
  DrawText(TextFormat("Rce: %s", ctx->player.race.race_id), 0, 43, 20, WHITE);
  DrawText(TextFormat("Rol: %s", ctx->player.role.role_id), 0, 64, 20, WHITE);
  DrawText(TextFormat("Bgd: %s", ctx->player.background), 0, 85, 20, WHITE);
  DrawText(TextFormat("Lyr: %s", ctx->player.layer), 0, 106, 20, WHITE);

  DrawText(TextFormat("Bdy: %d", ctx->player.body), 0, 127, 20, WHITE);
  DrawText(TextFormat("Dex: %d", ctx->player.dexterity), 0, 148, 20, WHITE);
  DrawText(TextFormat("Ftg: %d", ctx->player.fatigue), 0, 169, 20, WHITE);
  DrawText(TextFormat("Con: %d", ctx->player.connection), 0, 190, 20, WHITE);

  DrawText(TextFormat("H|P: %d", ctx->player.hp), 0, 211, 20, WHITE);
  DrawText(TextFormat("M|P: %d", ctx->player.mp), 0, 232, 20, WHITE);
  DrawText(TextFormat("Atk: %d", ctx->player.attack), 0, 253, 20, WHITE);
  DrawText(TextFormat("Pwr: %d", ctx->player.power), 0, 274, 20, WHITE);
  DrawText(TextFormat("Def: %d", ctx->player.defense), 0, 295, 20, WHITE);
  DrawText(TextFormat("Dur: %d", ctx->player.durability), 0, 316, 20, WHITE);
}

void charcreate_drawbox(Rectangle box, const char* label, bool selected) {
  const int fontSize = 20;
  const Color textColor = WHITE;
  const Color selectedColor = CLITERAL(Color){0, 0, 0, 50};
  const Color unselectedColor = CLITERAL(Color){255, 255, 255, 50};

  DrawRectangleRec(box, selected ? selectedColor : unselectedColor);

  int textWidth = MeasureText(label, fontSize);
  int textX = (int)(box.x + (box.width - textWidth) / 2);
  int textY = (int)(box.y + (box.height - fontSize) / 2);
  DrawText(label, textX, textY, fontSize, textColor);
}

void charcreate_capitalizeplayername(player_t* player) {
  for (int i = 0; i < letter_count; i++) {
    player->name[i] = tolower(player->name[i]);
  }
  player->name[0] = toupper(player->name[0]);
}

void charcreate_handle(GameContext* ctx) {
  DrawRectangle(0, 0, (int)ctx->setting.resolution.x, (int)ctx->setting.resolution.y,
                CLITERAL(Color){15, 59, 58, 255});
  charcreate_printdebuginfo(ctx);
  switch (ccstep) {
  case 0:
    // Name
    int key = GetCharPressed();
    while (key > 0) {
      if ((key >= 32) && (key <= 125) && (letter_count < PLAYER_MAXNAMELEN)) {
        name[letter_count] = (char)key;
        name[letter_count + 1] = '\0';
        letter_count++;
      }
      key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
      letter_count--;
      if (letter_count < 0) {
        letter_count = 0;
      }
      name[letter_count] = '\0';
    }
    DrawRectangle((int)(ctx->setting.resolution.x / 2.0f) - 100,
                  (int)(ctx->setting.resolution.y / 2.0f) - 100, 200, 90,
                  CLITERAL(Color){0, 0, 0, 50});
    Rectangle textbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                         (ctx->setting.resolution.y / 2.0f) - 90, 180, 30};
    Rectangle nameconfirmbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                (ctx->setting.resolution.y / 2.0f) - 50, 180, 30};
    DrawRectangleRec(textbox, LIGHTGRAY);
    DrawRectangleLines((int)textbox.x, (int)textbox.y, (int)textbox.width, (int)textbox.height,
                       BLACK);
    DrawText(name, (int)textbox.x + 5, (int)textbox.y + 5, 20, BLACK);
    DrawText("Enter name:",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("Enter name:", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 125, 20, WHITE);
    DrawRectangleRec(nameconfirmbox, DARKGRAY);
    DrawText("CONFIRM",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("CONFIRM", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 45, 20, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), nameconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 0) {
      if (name[0] == '\0') {
        strcpy(ctx->player.name, "UNNAMED");
      } else {
        strcpy(ctx->player.name, name);
        charcreate_capitalizeplayername(&ctx->player);
      }
      ccstep++;
    }

    break;
  case 1:
    // Gender
    DrawRectangle((int)(ctx->setting.resolution.x / 2.0f) - 100,
                  (int)(ctx->setting.resolution.y / 2.0f) - 100, 200, 140,
                  CLITERAL(Color){0, 0, 0, 50});
    DrawText(TextFormat("Choose gender:", letter_count),
             (int)(ctx->setting.resolution.x / 2.0f) -
                 (int)(MeasureText("Choose gender:", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 125, 20, WHITE);
    Rectangle genderconfirmbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                  ctx->setting.resolution.y / 2.0f, 180, 30};
    DrawRectangleRec(genderconfirmbox, DARKGRAY);
    DrawText("CONFIRM",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("CONFIRM", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) + 5, 20, WHITE);

    Rectangle mbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                      (ctx->setting.resolution.y / 2.0f) - 90, 85, 80};
    if (ctx->player.gender == 'M') {
      DrawRectangleRec(mbox, CLITERAL(Color){0, 0, 0, 50});
    } else {
      DrawRectangleRec(mbox, CLITERAL(Color){255, 255, 255, 50});
    }
    DrawText(TextFormat("M", 1), (int)(ctx->setting.resolution.x / 2.0f) - 55,
             (int)(ctx->setting.resolution.y / 2.0f) - 60, 20, WHITE);

    Rectangle fbox = {(ctx->setting.resolution.x / 2.0f) + 5,
                      (ctx->setting.resolution.y / 2.0f) - 90, 85, 80};
    if (ctx->player.gender == 'F') {
      DrawRectangleRec(fbox, CLITERAL(Color){0, 0, 0, 50});
    } else {
      DrawRectangleRec(fbox, CLITERAL(Color){255, 255, 255, 50});
    }
    DrawText(TextFormat("F", 1), (int)(ctx->setting.resolution.x / 2.0f) + 45,
             (int)(ctx->setting.resolution.y / 2.0f) - 60, 20, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), mbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 1) {
      gender_selected = 1;
      ctx->player.gender = 'M';
    }
    if (CheckCollisionPointRec(GetMousePosition(), fbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 1) {
      gender_selected = 1;
      ctx->player.gender = 'F';
    }
    if (CheckCollisionPointRec(GetMousePosition(), genderconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 1 && gender_selected == 1) {
      ccstep++;
    }
    break;
  case 2:
    // Race
    DrawRectangle((int)(ctx->setting.resolution.x / 2.0f) - 100,
                  (int)(ctx->setting.resolution.y / 2.0f) - 100, 200, 290,
                  CLITERAL(Color){0, 0, 0, 50});
    DrawText(TextFormat("Choose race:", letter_count),
             (int)(ctx->setting.resolution.x / 2.0f) -
                 (int)(MeasureText("Choose race:", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 125, 20, WHITE);

    Rectangle alfbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                        (ctx->setting.resolution.y / 2.0f) - 90, 180, 60};
    charcreate_drawbox(alfbox, "Alf", !strcmp(ctx->player.race.race_id, "Alf"));

    Rectangle mungbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                         (ctx->setting.resolution.y / 2.0f) - 20, 180, 60};
    charcreate_drawbox(mungbox, "Mung", !strcmp(ctx->player.race.race_id, "Mung"));

    Rectangle halfbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                         (ctx->setting.resolution.y / 2.0f) + 50, 180, 60};
    charcreate_drawbox(halfbox, "Half", !strcmp(ctx->player.race.race_id, "Half"));

    Rectangle raceconfirmbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                (ctx->setting.resolution.y / 2.0f) + 150, 180, 30};
    DrawRectangleRec(raceconfirmbox, DARKGRAY);
    DrawText("CONFIRM",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("CONFIRM", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) + 155, 20, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), alfbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 2) {
      race_selected = 1;
      ctx->player.race = race_select(1);
    }
    if (CheckCollisionPointRec(GetMousePosition(), mungbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 2) {
      race_selected = 1;
      ctx->player.race = race_select(2);
    }
    if (CheckCollisionPointRec(GetMousePosition(), halfbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 2) {
      race_selected = 1;
      ctx->player.race = race_select(3);
    }
    if (CheckCollisionPointRec(GetMousePosition(), raceconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 2 && race_selected == 1) {
      ccstep++;
    }
    break;
  case 3:
    // Role
    DrawRectangle((int)(ctx->setting.resolution.x / 2.0f) - 100,
                  (int)(ctx->setting.resolution.y / 2.0f) - 100, 200, 290,
                  CLITERAL(Color){0, 0, 0, 50});
    DrawText(TextFormat("Choose role:", letter_count),
             (int)(ctx->setting.resolution.x / 2.0f) -
                 (int)(MeasureText("Choose role:", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 125, 20, WHITE);

    Rectangle gruntbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                          (ctx->setting.resolution.y / 2.0f) - 90, 180, 60};
    charcreate_drawbox(gruntbox, "Grunt", !strcmp(ctx->player.role.role_id, "Grunt"));

    Rectangle thaumaturgebox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                (ctx->setting.resolution.y / 2.0f) - 20, 180, 60};
    charcreate_drawbox(thaumaturgebox, "Thaumaturge",
                       !strcmp(ctx->player.role.role_id, "Thaumaturge"));

    Rectangle burglarbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                            (ctx->setting.resolution.y / 2.0f) + 50, 180, 60};
    charcreate_drawbox(burglarbox, "Burglar", !strcmp(ctx->player.role.role_id, "Burglar"));

    Rectangle roleconfirmbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                (ctx->setting.resolution.y / 2.0f) + 150, 180, 30};
    DrawRectangleRec(roleconfirmbox, DARKGRAY);
    DrawText("CONFIRM",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("CONFIRM", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) + 155, 20, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), gruntbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 3) {
      role_selected = 1;
      ctx->player.role = role_select(1);
    }
    if (CheckCollisionPointRec(GetMousePosition(), thaumaturgebox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 3) {
      role_selected = 1;
      ctx->player.role = role_select(2);
    }
    if (CheckCollisionPointRec(GetMousePosition(), burglarbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 3) {
      role_selected = 1;
      ctx->player.role = role_select(3);
    }
    if (CheckCollisionPointRec(GetMousePosition(), roleconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 3 && role_selected == 1) {
      ccstep++;
    }

    break;
  case 4:
    // Background
    DrawRectangle((int)(ctx->setting.resolution.x / 2.0f) - 100,
                  (int)(ctx->setting.resolution.y / 2.0f) - 100, 200, 290,
                  CLITERAL(Color){0, 0, 0, 50});
    DrawText(TextFormat("Choose background:", letter_count),
             (int)(ctx->setting.resolution.x / 2.0f) -
                 (int)(MeasureText("Choose background:", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 125, 20, WHITE);

    Rectangle bg1box = {(ctx->setting.resolution.x / 2.0f) - 90,
                        (ctx->setting.resolution.y / 2.0f) - 90, 180, 60};
    charcreate_drawbox(bg1box, "Bg1", !strcmp(ctx->player.background, "Bg1"));

    Rectangle bg2box = {(ctx->setting.resolution.x / 2.0f) - 90,
                        (ctx->setting.resolution.y / 2.0f) - 20, 180, 60};
    charcreate_drawbox(bg2box, "Bg2", !strcmp(ctx->player.background, "Bg2"));

    Rectangle bg3box = {(ctx->setting.resolution.x / 2.0f) - 90,
                        (ctx->setting.resolution.y / 2.0f) + 50, 180, 60};
    charcreate_drawbox(bg3box, "Bg3", !strcmp(ctx->player.background, "Bg3"));

    Rectangle backgroundconfirmbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                      (ctx->setting.resolution.y / 2.0f) + 150, 180, 30};
    DrawRectangleRec(backgroundconfirmbox, DARKGRAY);
    DrawText("CONFIRM",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("CONFIRM", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) + 155, 20, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), bg1box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 4) {
      background_selected = 1;
      strcpy(ctx->player.background, "Bg1");
    }
    if (CheckCollisionPointRec(GetMousePosition(), bg2box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 4) {
      background_selected = 1;
      strcpy(ctx->player.background, "Bg2");
    }
    if (CheckCollisionPointRec(GetMousePosition(), bg3box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 4) {
      background_selected = 1;
      strcpy(ctx->player.background, "Bg3");
    }
    if (CheckCollisionPointRec(GetMousePosition(), backgroundconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 4 && background_selected == 1) {
      ccstep++;
    }
    break;
  case 5:
    // Layer
    DrawRectangle((int)(ctx->setting.resolution.x / 2.0f) - 100,
                  (int)(ctx->setting.resolution.y / 2.0f) - 100, 200, 290,
                  CLITERAL(Color){0, 0, 0, 50});
    DrawText(TextFormat("Choose layer:", letter_count),
             (int)(ctx->setting.resolution.x / 2.0f) -
                 (int)(MeasureText("Choose layer:", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) - 125, 20, WHITE);

    Rectangle layer1box = {(ctx->setting.resolution.x / 2.0f) - 90,
                           (ctx->setting.resolution.y / 2.0f) - 90, 180, 60};
    charcreate_drawbox(layer1box, "Layer1", !strcmp(ctx->player.layer, "Layer1"));

    Rectangle layer2box = {(ctx->setting.resolution.x / 2.0f) - 90,
                           (ctx->setting.resolution.y / 2.0f) - 20, 180, 60};
    charcreate_drawbox(layer2box, "Layer2", !strcmp(ctx->player.layer, "Layer2"));

    Rectangle layer3box = {(ctx->setting.resolution.x / 2.0f) - 90,
                           (ctx->setting.resolution.y / 2.0f) + 50, 180, 60};
    charcreate_drawbox(layer3box, "Layer3", !strcmp(ctx->player.layer, "Layer3"));

    Rectangle layerconfirmbox = {(ctx->setting.resolution.x / 2.0f) - 90,
                                 (ctx->setting.resolution.y / 2.0f) + 150, 180, 30};
    DrawRectangleRec(layerconfirmbox, DARKGRAY);
    DrawText("CONFIRM",
             (int)(ctx->setting.resolution.x / 2.0f) - (int)(MeasureText("CONFIRM", 20) / 2.0f),
             (int)(ctx->setting.resolution.y / 2.0f) + 155, 20, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), layer1box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 5) {
      layer_selected = 1;
      strcpy(ctx->player.layer, "Layer1");
    }
    if (CheckCollisionPointRec(GetMousePosition(), layer2box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 5) {
      layer_selected = 1;
      strcpy(ctx->player.layer, "Layer2");
    }
    if (CheckCollisionPointRec(GetMousePosition(), layer3box) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 5) {
      layer_selected = 1;
      strcpy(ctx->player.layer, "Layer3");
    }
    if (CheckCollisionPointRec(GetMousePosition(), layerconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 5 && layer_selected == 1) {
      ccstep++;
    }
    break;
  }
}
