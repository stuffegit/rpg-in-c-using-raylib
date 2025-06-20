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

void charcreate_printdebuginfo(player_t player, Font nfont) {
  DrawTextEx(nfont, TextFormat("Nam: %s", player.name), (Vector2){0, 1}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Gen: %c", player.gender), (Vector2){0, 31}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Rce: %s", player.race.race_id), (Vector2){0, 61}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Rol: %s", player.role.role_id), (Vector2){0, 91}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Bgd: %s", player.background), (Vector2){0, 121}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Lyr: %s", player.layer), (Vector2){0, 151}, 32, 1, WHITE);

  DrawTextEx(nfont, TextFormat("Bdy: %d", player.body), (Vector2){0, 181}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Dex: %d", player.dexterity), (Vector2){0, 211}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Ftg: %d", player.fatigue), (Vector2){0, 241}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Con: %d", player.connection), (Vector2){0, 271}, 32, 1, WHITE);

  DrawTextEx(nfont, TextFormat("H|P: %d", player.hp), (Vector2){0, 301}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("M|P: %d", player.mp), (Vector2){0, 331}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Atk: %d", player.attack), (Vector2){0, 361}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Pwr: %d", player.power), (Vector2){0, 391}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Def: %d", player.defense), (Vector2){0, 421}, 32, 1, WHITE);
  DrawTextEx(nfont, TextFormat("Dur: %d", player.durability), (Vector2){0, 451}, 32, 1, WHITE);
}

void charcreate_drawbox(Rectangle box, GameContext* ctx, const char* label, bool selected) {
  const int fontSize = 32.0f;
  const Color textColor = WHITE;
  const Color selectedColor = CLITERAL(Color){0, 0, 0, 50};
  const Color unselectedColor = CLITERAL(Color){255, 255, 255, 50};

  DrawRectangleRec(box, selected ? selectedColor : unselectedColor);

  int textWidth = MeasureText(label, fontSize);
  int textX = (int)(box.x + (box.width - textWidth) / 2);
  int textY = (int)(box.y + (box.height - fontSize) / 2);
  DrawTextEx(ctx->setting.nfont, label, (Vector2){textX, textY}, fontSize, 1, textColor);
}

void charcreate_drawboxbackground(GameContext* ctx, char* title, int width, int height) {
  DrawRectangle(
      0, 0, (int)ctx->setting.resolution.x, (int)ctx->setting.resolution.y,
      CLITERAL(Color){15, 59, 58, 255});
  DrawRectangle(
      (ctx->setting.resolution.x / 2) - (width / 2), (ctx->setting.resolution.y / 2) - (height / 2),
      width, height, CLITERAL(Color){0, 0, 0, 50});

  float fontsize = 32.0f;
  Vector2 textsize = MeasureTextEx(ctx->setting.nfont, title, fontsize, 1);
  Vector2 textpos = {
      (ctx->setting.resolution.x / 2.0f) - (textsize.x / 2.0f),
      (ctx->setting.resolution.y / 2.0f) - (height / 2.0f) - textsize.y};

  DrawTextEx(ctx->setting.nfont, title, textpos, fontsize, 1, WHITE);
  charcreate_printdebuginfo(ctx->player, ctx->setting.nfont);
}

void charcreate_drawconfirmbox(Rectangle box, GameContext* ctx) {
  Vector2 confirmsize = MeasureTextEx(ctx->setting.nfont, "CONFIRM", 32.0f, 1.0f);
  DrawRectangleRec(box, DARKGRAY);
  DrawTextEx(
      ctx->setting.nfont, "CONFIRM",
      (Vector2){(ctx->setting.resolution.x / 2) - confirmsize.x / 2, box.y}, 32, 1, WHITE);
}

void charcreate_capitalizeplayername(player_t* player) {
  for (int i = 0; i < letter_count; i++) {
    player->name[i] = tolower(player->name[i]);
  }
  player->name[0] = toupper(player->name[0]);
}

void charcreate_handle(GameContext* ctx) {
  switch (ccstep) {
  case 0:
    // Name
    charcreate_drawboxbackground(ctx, "Enter name:", 200, 90);
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
    Rectangle textbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 35, 180, 30};
    DrawRectangleRec(textbox, LIGHTGRAY);
    DrawRectangleLines(
        (int)textbox.x, (int)textbox.y, (int)textbox.width, (int)textbox.height, BLACK);

    Rectangle nameconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 5, 180, 30};
    charcreate_drawconfirmbox(nameconfirmbox, ctx);

    DrawText(name, (int)textbox.x + 5, (int)textbox.y + 5, 20, BLACK);
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
    charcreate_drawboxbackground(ctx, "Choose gender:", 200, 140);
    Rectangle genderconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 30, 180, 30};
    charcreate_drawconfirmbox(genderconfirmbox, ctx);

    Rectangle mbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 60, 85, 80};
    if (ctx->player.gender == 'M') {
      DrawRectangleRec(mbox, CLITERAL(Color){0, 0, 0, 50});
    } else {
      DrawRectangleRec(mbox, CLITERAL(Color){255, 255, 255, 50});
    }
    DrawTextEx(
        ctx->setting.nfont, TextFormat("M", 1),
        (Vector2){(ctx->setting.resolution.x / 2.0f) - 60, (ctx->setting.resolution.y / 2.0f) - 35},
        32, 1, WHITE);

    Rectangle fbox = {
        (ctx->setting.resolution.x / 2.0f) + 5, (ctx->setting.resolution.y / 2.0f) - 60, 85, 80};
    if (ctx->player.gender == 'F') {
      DrawRectangleRec(fbox, CLITERAL(Color){0, 0, 0, 50});
    } else {
      DrawRectangleRec(fbox, CLITERAL(Color){255, 255, 255, 50});
    }
    DrawTextEx(
        ctx->setting.nfont, TextFormat("F", 1),
        (Vector2){(ctx->setting.resolution.x / 2.0f) + 40, (ctx->setting.resolution.y / 2.0f) - 35},
        32, 1, WHITE);

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
    charcreate_drawboxbackground(ctx, "Choose race:", 200, 290);
    Rectangle alfbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 135, 180, 60};
    charcreate_drawbox(alfbox, ctx, "Alf", !strcmp(ctx->player.race.race_id, "Alf"));

    Rectangle mungbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 65, 180, 60};
    charcreate_drawbox(mungbox, ctx, "Mung", !strcmp(ctx->player.race.race_id, "Mung"));

    Rectangle halfbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 5, 180, 60};
    charcreate_drawbox(halfbox, ctx, "Half", !strcmp(ctx->player.race.race_id, "Half"));

    Rectangle raceconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 105, 180, 30};
    charcreate_drawconfirmbox(raceconfirmbox, ctx);

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
    charcreate_drawboxbackground(ctx, "Choose role:", 200, 290);
    Rectangle gruntbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 135, 180, 60};
    charcreate_drawbox(gruntbox, ctx, "Grunt", !strcmp(ctx->player.role.role_id, "Grunt"));

    Rectangle thaumaturgebox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 65, 180, 60};
    charcreate_drawbox(
        thaumaturgebox, ctx, "Theurgist", !strcmp(ctx->player.role.role_id, "Theurgist"));

    Rectangle burglarbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 5, 180, 60};
    charcreate_drawbox(burglarbox, ctx, "Burglar", !strcmp(ctx->player.role.role_id, "Burglar"));

    Rectangle roleconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 105, 180, 30};
    charcreate_drawconfirmbox(roleconfirmbox, ctx);

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
    charcreate_drawboxbackground(ctx, "Choose background:", 200, 290);
    Rectangle bg1box = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 135, 180, 60};
    charcreate_drawbox(bg1box, ctx, "Bg1", !strcmp(ctx->player.background, "Bg1"));

    Rectangle bg2box = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 65, 180, 60};
    charcreate_drawbox(bg2box, ctx, "Bg2", !strcmp(ctx->player.background, "Bg2"));

    Rectangle bg3box = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 5, 180, 60};
    charcreate_drawbox(bg3box, ctx, "Bg3", !strcmp(ctx->player.background, "Bg3"));

    Rectangle backgroundconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 105, 180, 30};
    charcreate_drawconfirmbox(backgroundconfirmbox, ctx);

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
    charcreate_drawboxbackground(ctx, "Choose layer:", 200, 290);
    Rectangle layer1box = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 135, 180, 60};
    charcreate_drawbox(layer1box, ctx, "Layer1", !strcmp(ctx->player.layer, "Layer1"));

    Rectangle layer2box = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) - 65, 180, 60};
    charcreate_drawbox(layer2box, ctx, "Layer2", !strcmp(ctx->player.layer, "Layer2"));

    Rectangle layer3box = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 5, 180, 60};
    charcreate_drawbox(layer3box, ctx, "Layer3", !strcmp(ctx->player.layer, "Layer3"));

    Rectangle layerconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 105, 180, 30};
    charcreate_drawconfirmbox(layerconfirmbox, ctx);

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
  case 6:
    // Summary
    charcreate_drawboxbackground(ctx, "Summary:", 400, 290);
    Rectangle summarybox = {
        (ctx->setting.resolution.x / 2.0f) - 190, (ctx->setting.resolution.y / 2.0f) - 135, 380,
        230};
    DrawRectangleRec(summarybox, CLITERAL(Color){15, 59, 58, 255});
    DrawText(
        TextFormat(
            "You are %s.\nA %s from %s\nworking as a %s for\nthe %s layer.", ctx->player.name,
            (ctx->player.gender == 'M') ? "man" : "woman", ctx->player.background,
            ctx->player.role.role_id, ctx->player.layer),
        (int)(ctx->setting.resolution.x / 2.0f) - 180, (int)(ctx->setting.resolution.y / 2.0f) - 85,
        32, WHITE);

    Rectangle summaryconfirmbox = {
        (ctx->setting.resolution.x / 2.0f) - 90, (ctx->setting.resolution.y / 2.0f) + 105, 180, 30};
    charcreate_drawconfirmbox(summaryconfirmbox, ctx);

    if (CheckCollisionPointRec(GetMousePosition(), summaryconfirmbox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ccstep == 6) {
      ctx->state = STATE_GAME;
    }
    break;
  }
}
