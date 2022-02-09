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

tileMap* tileMap_load();

void tileMap_draw();


#endif