#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "simple_json.h"

#include "gfc_audio.h"
#include "borders.h"

#include "entity.h"


typedef struct {

	Uint8 inuse; //to tell whether that level is loaded or not
	Uint8 taken; //if the memory is taken in space
	Uint8 plantAccess; //allows you to plant or not

	Sprite* image; //the background to load 

	Sound* music; //the music that plays for the world.

	Uint32 totalBorders; //the amount of borders to load in the level

	char* levelTransfer; //the level that will be moved to when border is touched


}level;

/*
* the level that is currently running
*/
level* currentLevel;


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
void level_draw();

/*
* @brief loads all the borders for the level by json
* @param the json to load from
*/
void level_load_borders(SJson *json);

/*
* @brief handles all the updates for a level
* @param the level to update
*/
void level_update();

void level_entity_load(SJson *json);

void level_unload();

/*
* @brief makes a smooth transition between levels
* @param the filename of the level
* @param the border that was collided with
*/
void level_switch(char* filename, border* bord);



#endif
