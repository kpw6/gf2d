#include "tilemap.h"
#include "tileset.h"

#include "simple_json.h"
#include "simple_logger.h"

tileMap* tileMap_load(char *filename) {
    int i, r, c, e;
    const char* spriteFile = NULL;
    SJson* json, * rows, * columns, * element;
    tileMap* map;
    int tile_width;
    int tile_height;
    int tile_count;

    int tilemap_width;
    int tilemap_height;
    int tilemap_count;
    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)return NULL;
    map = tileMap_new();

    spriteFile = sj_get_string_value(sj_object_get_value(json, "tileset"));

    sj_get_integer_value(sj_object_get_value(json, "tile_width"), &tile_width);
    sj_get_integer_value(sj_object_get_value(json, "tile_height"), &tile_height);
    sj_get_integer_value(sj_object_get_value(json, "tile_count"), &tile_count);
   
    map->tileset = tileSet_load(
        (char*)spriteFile,
        tile_width,
        tile_height,
        tile_count);

    rows = sj_object_get_value(json, "tile_map");
    tilemap_height = sj_array_get_count(rows);
    if (!tilemap_height)
    {
        slog("tilemap contains no data!");
        sj_free(json);
        return map;
    }
    columns = sj_array_get_nth(rows, 0);
    tilemap_width = sj_array_get_count(columns);

    tilemap_count = tilemap_width * tilemap_height;

    map->tilemap = (Uint32*)gfc_allocate_array(sizeof(Uint32), tilemap_count);
    if (!map->tilemap)
    {
        sj_free(json);
        return map;
    }

    map->tileMap_count = tilemap_count;
    map->tileMap_width = tilemap_width;

    for (i = 0, r = 0; r < tilemap_height; r++)
    {
        columns = sj_array_get_nth(rows, r);
        if (!columns)continue;
        for (c = 0; c < tilemap_width; c++)
        {
            element = sj_array_get_nth(columns, c);
            if (!element)continue;
            sj_get_integer_value(element, &e);
            map->tilemap[i++] = e;
        }
    }

    sj_free(json);
    return map;
}

tileMap* tileMap_new() {
	tileMap* map;
	map = (tileMap*)malloc(sizeof(tileMap));
	if (!map)
	{
		slog("failed to allocate memory for a new tilemap");
		return NULL;
	}
	memset(map, 0, sizeof(tileMap));
	return map;
}

void tileMap_free(tileMap* map) {
    if (!map)return;
    tileSet_free(map->tileset);
    free(map->tilemap);
    free(map);
}

void tileMap_draw(tileMap* map) {
    int i;
    if (!map)return;
    if (!map->tileset)return;
    if (!map->tilemap)return;
    for (i = 0; i < map->tileMap_count; i++)
    {
        if (!map->tilemap[i])continue;
        tileSet_draw(
            map->tileset,
            map->tilemap[i] - 1,
            vector2d(
                (i % map->tileMap_width) * map->tileset->tile_width,
                (i / map->tileMap_width) * map->tileset->tile_height));
    }
}