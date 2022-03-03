#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "simple_json.h"

#include "entity.h"

typedef struct {
	Uint8 inuse; //to tell whether that level is loaded or not
	Uint8 taken; //if the memory is taken in space

	Sprite* image; //the background to load 

	Uint32 totalBorders; //the amount of borders to load in the level


}level;


void level_manager_close();
void level_manager_init(Uint32 maxLevels);
/*
* @brief frees a level from memory
* @param the level you want to free
*/
void level_free(level *lev);

/*
* @brief loads a level from json
* @param the json file you want to load
*/
level *level_load(char* filename);

/*
* @brief creates a new level
*/
level *level_new();

/*
* @brief draws the level on the screen
* @param the level that is being drawn
*/
void level_draw(level *lev);

/*
* @brief loads all the borders for the level by json
* @param the json to load from
*/
void level_load_borders(SJson *json);

/*
* @brief handles all the updates for a level
* @param the level to update
*/
void level_update(level* lev);



#endif
