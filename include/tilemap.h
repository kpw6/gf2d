#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "tileset.h"

typedef struct {

	TextLine filename;
	tileSet* tileset;
	Uint32* tilemap;
	Uint32 tileMap_count;
	Uint32 tileMap_width;
}tileMap;

/*
* @brief frees a tilemap from memory
* @param the tilemap to free
*/
void tileMap_free(tileMap* map);

/*
* @brief loads from json the file needed for a new tilemap
* @param the file of the json
* @return the tilemap
*/
tileMap* tileMap_load(char* filename);

/*
* @brief creates a new tilemap in memory for use
* @return the new tilemap
*/
tileMap* tileMap_new();

/*
* @brief draws a tilemap onto the screen
* @param the tilemap to draw
*/
void tileMap_draw(tileMap* map);


#endif