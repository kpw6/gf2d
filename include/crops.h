#ifndef __CROPS_H__
#define __CROPS_H__

#include "entity.h"


void crops_think(Entity* crop);

void crops_ontouch(Entity* self, Entity* other);

/*
* @brief Creates a new crop for use
*/
Entity* crops_new(char* filename, cropType type, Vector2D position);

#endif