#include "simple_logger.h"

#include "tileset.h"

typedef struct{

	tileSet* tileSet_list;
	Uint32 tileSet_count;

}tileSetManager;

static tileSetManager tileSetM = { 0 };

void tileSet_manager_close() {
	int i;
	for (i = 0; i < tileSetM.tileSet_count; i++) {
		tileSet_free(&tileSetM.tileSet_list[i]);
	}
	slog("Tile set manager closed");
}

void tileSet_manager_init(Uint32 tileset_count) {
	if (tileset_count <= 0) {
		slog("Tileset can't be below 0");
		return;
	}
	tileSetM.tileSet_list = (tileSet*)gfc_allocate_array(sizeof(tileSet), tileset_count);
	if (!tileSetM.tileSet_list) {
		return;
	}
	tileSetM.tileSet_count = tileset_count;
	slog("Tile set manager initlazied");
	atexit(tileSet_manager_close);
}

void tileSet_free(tileSet* tileset) {
	if (!tileset) {
		slog("No tileset to free");
		return;
	}
	if (tileset->tile_image) {
		free(tileset->tile_image);
	}
	memset(tileset, 0, sizeof(tileset));
}

tileSet* tileSet_new() {
	int i;
	for (i = 0; i < tileSetM.tileSet_count; i++) {
		if (!tileSetM.tileSet_list[i]._inuse) {
			tileSetM.tileSet_list[i]._inuse = 1;
			return (&tileSetM.tileSet_list[i]);
		}
	}
	slog("no space free for new entity");
	return;
}

tileSet* tileSet_load(char* filename, Uint32 tilewidth, Uint32 tileLength, Uint32 tileCount) {
	tileSet* tileset;
	if (!filename) {
		return;
	}
	tileset = tileSet_new();

}

void tileSet_draw(tileSet* tileset, Uint32 tile, Vector2D position);