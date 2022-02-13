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
	free(tileSetM.tileSet_list);
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

void tileSet_delete(tileSet* tileset) {
	if (!tileset)return;
	if (tileset->_refcount > 0)
	{
		slog("deleting tileset %s.  However refcount is greater than 0", tileset->filename);
	}
	gf2d_sprite_free(tileset->tile_image);
	memset(tileset, 0, sizeof(tileSet));
}

void tileSet_free(tileSet* tileset) {
	if (!tileset)return;
	if (tileset->_refcount == 0)
	{
		slog("trying to free %s tileset more times than loaded", tileset->filename);
	}
	tileset->_refcount--;
	if (tileset->_refcount == 0)
	{
		tileSet_delete(tileset);
	}
}

tileSet* tile_get_filename(char* filename) {
	int i;
	if (!filename)return NULL;
	for (i = 0; i < tileSetM.tileSet_count; i++)
	{
		if (!tileSetM.tileSet_list[i]._refcount)continue;
		if (gfc_line_cmp(filename, tileSetM.tileSet_list[i].filename) == 0)
		{
			return &tileSetM.tileSet_list[i];
		}
	}
	return NULL;
}

tileSet* tileSet_new() {
	int i;
	for (i = 0; i < tileSetM.tileSet_count; i++)
	{
		if (!tileSetM.tileSet_list[i]._refcount)
		{
			tileSetM.tileSet_list[i]._refcount = 1;
			return &tileSetM.tileSet_list[i];
		}
	}
	slog("we are out of memory for tile sets");
	return NULL;
}

tileSet* tileSet_load(char* filename, Uint32 tileWidth, Uint32 tileHeight, Uint32 tileCount) {
	tileSet* tileset;
	if (!filename)return NULL;

	tileset = tile_get_filename(filename);
	if (tileset != NULL)
	{
		tileset->_refcount++;
		return tileset;
	}


	tileset = tileSet_new();
	if (!tileset)return NULL;
	tileset->tile_image = gf2d_sprite_load_all(
		filename,
		tileWidth,
		tileHeight,
		tileCount);
	gfc_line_cpy(tileset->filename, filename);
	tileset->tile_width = tileWidth;
	tileset->tile_height = tileHeight;
	tileset->tile_count = tileCount;

	return tileset;
}

void tileSet_draw(tileSet* tileset, Uint32 tile, Vector2D position) {
	if (!tileset)return;
	if (!tileset->tile_image)return;// nothing to draw
	gf2d_sprite_draw(
		tileset->tile_image,
		position,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		tile);
}