#ifndef __CROPS_H__
#define __CROPS_H__

#include "entity.h"



/*
* @brief the think function for the crop
*/
void crops_think(Entity* crop);


/*
* @brief the touch function for the crop entities
* @param itself
* @param entity that touched or touched it.
*/
void crops_ontouch(Entity* self, Entity* other);

/*
* @brief Creates a new crop for use
* @param the file name that the json loads from
* @param the enum type that decides what type of crop to load
* @param the position where the crop will spawn
*/
Entity* crops_new(char* filename, cropType type, Vector2D position);

#endif