#ifndef __TILESET_H__
#define __TILESET_H__

#include "gfc_text.h"

#include "gf2d_sprite.h"

typedef struct {

	Uint8 _refcount;

	TextLine filename;

	Sprite* tile_image; //image loaded for a tile set

	Uint32 tile_width;
	Uint32 tile_height;
	Uint32 tile_count;

}tileSet;

/*
* @brief initialized the tileset manager
* @param the amount of tilesets to put into memory
*/
void tileSet_manager_init(Uint32 tileset_count);

/*
* @brief frees a tileset from memory
* @param the tileset to free
*/
void tileSet_free(tileSet* tileset);

/*
* @brief checks to make sure the file isn't in use already
* @param the file to check
* @return NULL if file is in use
* @return filename if not in use
*/
tileSet* tile_get_filename(char *filename);

/*
* @brief creates a new tileset in memory
* @return the new tileset
*/
tileSet* tileSet_new();

/*
* @brief the tileset to load from filename
* @param the file to load from files
* @param the width of the tileset
* @param the height of the tileset
* @param the amount of tiles in the tileset
* @return the tileset that was loaded
*/
tileSet* tileSet_load(char* filename, Uint32 tilewidth, Uint32 tileHeight, Uint32 tileCount);

/*
* @brief draws a tileset onto the screen
* @param the singular tile to draw
* @param the position of where to draw the tile
*/
void tileSet_draw(tileSet* tileset, Uint32 tile, Vector2D position);

#endif
