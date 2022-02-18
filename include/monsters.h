#ifndef __MONSTERS_H__
#define __MONSTERS_H__

#include "entity.h"

void monsters_think(Entity* self);

void monsters_ontouch(Entity* self);

Entity* monsters_new(char* filename, monsterType type, Vector2D position);

#endif