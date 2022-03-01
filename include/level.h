#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "entity.h"

typedef struct {

	Sprite* image; //the background to load 

	Uint32 totalBorders; //the amount of borders to load in the level


}level;
/*
* @brief frees a level from memory
* @param the level you want to free
*/
void level_free(level *lev);

/*
* @brief loads a level from json
* @param the json file you want to load
*/
level level_load(char* filename);

/*
* @brief creates a new level
*/
level level_new();

/*
* @brief draws the level on the screen
* @param the level that is being drawn
*/
void level_draw(level *lev);



#endif
