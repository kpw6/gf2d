#ifndef __TILESET_H__
#define __TILESET_H__

#include "gfc_text.h"

#include "gf2d_sprite.h"

typedef struct {

	Uint8 _inuse;

	TextLine filename;

	Sprite* tile_image; //image loaded for a tile set

	Uint32 tile_width;
	Uint32 tile_height;
	Uint32 tile_count;

}tileSet;

void tileSet_manager_init(Uint32 tileset_count);

void tileSet_free(tileSet* tileset);

tileSet* tileSet_new();

tileSet* tileSet_load(char* filename, Uint32 tilewidth, Uint32 tileLength, Uint32 tileCount);

void tileSet_draw(tileSet* tileset, Uint32 tile, Vector2D position);

#endif
