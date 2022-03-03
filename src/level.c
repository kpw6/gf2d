#include "simple_json.h"
#include "simple_logger.h"

#include "level.h"

typedef struct {

	level* level_list;
	Uint32 level_count;

}levelManager;

static levelManager LM = { 0 };

void level_manager_close() {
	int i;
	for (i = 0; i < LM.level_count; i++) {
		tileSet_free(&LM.level_list[i]);
	}
	free(LM.level_list);
	slog("Tile set manager closed");
}

void level_manager_init(Uint32 maxLevels) {
	int i;
	if (maxLevels <= 0) {
		slog("not enough levels to create");
		return;
	}
	LM.level_list = (level*)gfc_allocate_array(sizeof(level), maxLevels);
	if (!LM.level_list) return;
	LM.level_count = maxLevels;
	atexit(level_manager_close);
	slog("Level Manager Initilialzed");
}

void level_free(level* lev) {
	if (!lev) return;
	free(lev);

}

level *level_load(char* filename) {
	SJson *json, borders;
	level* lev;


	if (!filename) return;
	lev = level_new();
	if (!lev) {
		slog("failed to create level");
		return;
	}
	json = sj_load(filename);
	if (!json) {
		slog("level not found");
		return;
	}
	lev->image = gf2d_sprite_load_image(sj_get_string_value(sj_object_get_value(json, "map")));
	level_load_borders(json);
	


	free(json);
	return lev;


}

level *level_new() {
	for (int i = 0; i < LM.level_count; i++) {
		if (!LM.level_list[i].taken) {
			LM.level_list[i].taken = 1;
			return &LM.level_list[i];
		}
	}
	slog("out of memory");
	return NULL;

}

void level_draw(level* lev) {
	if (!lev) return;
	gf2d_sprite_draw_image(lev->image, vector2d(0, 0));
	entity_draw_all();

}

void border_onTouch(Entity* self, Entity* other) {
	pushback_entity(self, other);
}
void level_load_borders(SJson* json) {
	SJson* borders, *border, *min, *max;
	Entity *bord;
	float x, y;
	int count;
	borders = sj_object_get_value(json, "borders");
	if (!borders) {
		slog("no borders for you");
	}
	count = sj_array_get_count(borders);
	for (int i = 0; i < count; i++) {
		border = sj_array_get_nth(borders, i);
		if (!border) continue;
		bord = entity_new();
		if (!bord) {
			slog("couldn't create border");
			return;
		}
		min = sj_object_get_value(border, "min");
		if (!min) {
			slog("no min found");
		}
		sj_get_float_value(sj_array_get_nth(min, 0), &x);
		sj_get_float_value(sj_array_get_nth(min, 1), &y);
		slog("this works %f", y);
		slog("x = %f", x);
		bord->min = vector2d(x, y);
		max = sj_object_get_value(border, "max");
		sj_get_float_value(sj_array_get_nth(max, 0), &x);
		sj_get_float_value(sj_array_get_nth(max, 1), &y);
		slog("this works %f", y);
		slog("x = %f", x);
		bord->max = vector2d(x, y);
		bord->position = vector2d(0, 0);
		bord->sprite = gf2d_sprite_load_all("images/perlin-grey.png", 1, 1, 1);
		bord->frame = 1;
		bord->onTouch = border_onTouch;
	}
	free(borders);
	
}


