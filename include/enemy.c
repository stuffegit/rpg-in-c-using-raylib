#include "enemy.h"
#include "string.h"
#include "stdio.h"
#include "cJSON.h"

char jsonbuffer[2048];

void enemy_init(Enemy* enemy) {
  enemy->level = 0;
  strcpy(enemy->name, "Spökmonster");

  enemy->hp = 0;
  enemy->hpmax = 0;
  enemy->mp = 0;
  enemy->mpmax = 0;
  enemy->attack = 0;
  enemy->power = 0;
  enemy->defense = 0;
  enemy->durability = 0;

  enemy->moneydrop = 0;
  enemy->xp = 0;
  enemy->ap = 0;
}

void enemy_updatestats(Enemy* enemy) {
  enemy->hp = 0;
  enemy->mp = 0;
  enemy->attack = 0;
  enemy->power = 0;
  enemy->defense = 0;
  enemy->durability = 0;
}

void enemy_load_from_json(Enemy* enemy, char* enemybp) {
  FILE* fp = fopen(enemybp, "r");
  if (!fp) {
    perror("Failed to open enemy file");
    return;
  }

  size_t read_size = fread(jsonbuffer, 1, sizeof(jsonbuffer) - 1, fp);
  jsonbuffer[read_size] = '\0';
  fclose(fp);

  cJSON* enemy_temp = cJSON_Parse(jsonbuffer);
  if (!enemy_temp) {
    printf("Failed to parse enemy JSON\n");
    return;
  }

  // Integers
  cJSON* level = cJSON_GetObjectItem(enemy_temp, "level");
  if (cJSON_IsNumber(level))
    enemy->level = level->valueint;

  cJSON* hp = cJSON_GetObjectItem(enemy_temp, "hp");
  if (cJSON_IsNumber(hp))
    enemy->hp = hp->valueint;

  cJSON* hpmax = cJSON_GetObjectItem(enemy_temp, "hpmax");
  if (cJSON_IsNumber(hpmax))
    enemy->hpmax = hpmax->valueint;

  cJSON* mp = cJSON_GetObjectItem(enemy_temp, "mp");
  if (cJSON_IsNumber(mp))
    enemy->mp = mp->valueint;

  cJSON* mpmax = cJSON_GetObjectItem(enemy_temp, "mpmax");
  if (cJSON_IsNumber(mpmax))
    enemy->mpmax = mpmax->valueint;

  cJSON* attack = cJSON_GetObjectItem(enemy_temp, "attack");
  if (cJSON_IsNumber(attack))
    enemy->attack = attack->valueint;

  cJSON* power = cJSON_GetObjectItem(enemy_temp, "power");
  if (cJSON_IsNumber(power))
    enemy->power = power->valueint;

  cJSON* defense = cJSON_GetObjectItem(enemy_temp, "defense");
  if (cJSON_IsNumber(defense))
    enemy->defense = defense->valueint;

  cJSON* durability = cJSON_GetObjectItem(enemy_temp, "durability");
  if (cJSON_IsNumber(durability))
    enemy->durability = durability->valueint;

  cJSON* moneydrop = cJSON_GetObjectItem(enemy_temp, "moneydrop");
  if (cJSON_IsNumber(moneydrop))
    enemy->moneydrop = moneydrop->valueint;

  cJSON* xp = cJSON_GetObjectItem(enemy_temp, "xp");
  if (cJSON_IsNumber(xp))
    enemy->xp = xp->valueint;

  cJSON* ap = cJSON_GetObjectItem(enemy_temp, "ap");
  if (cJSON_IsNumber(ap))
    enemy->ap = ap->valueint;

  // Strings
  cJSON* name = cJSON_GetObjectItem(enemy_temp, "name");
  if (cJSON_IsString(name) && name->valuestring) {
    strncpy(enemy->name, name->valuestring, ENEMY_MAXNAMELEN);
    enemy->name[ENEMY_MAXNAMELEN] = '\0'; // Ensure null-terminated
  }

  cJSON* origin = cJSON_GetObjectItem(enemy_temp, "origin");
  if (cJSON_IsString(origin) && origin->valuestring) {
    strncpy(enemy->origin, origin->valuestring, ENEMY_MAXIDLEN);
    enemy->origin[ENEMY_MAXIDLEN] = '\0';
  }

  cJSON_Delete(enemy_temp);
}
