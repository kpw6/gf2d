#include "simple_json.h"
#include "simple_logger.h"

#include "level.h"
#include "borders.h"

typedef struct {

	level* level_list;
	Uint32 level_count;

}levelManager;

static levelManager LM = { 0 };

void level_manager_close() {
	int i;
	for (i = 0; i < LM.level_count; i++) {
		level_free(&LM.level_list[i]);
	}
	free(LM.level_list);
	slog("level manager closed");
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
	if (lev->image) {
		gf2d_sprite_free(lev->image);
	}
	memset(lev, 0, sizeof(level));

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
	borders_draw_all();

}

void level_load_borders(SJson* json) {
	SJson* borders, *bordert, *min, *max;
	border *bord;
	float x, y;
	int count, type;
	borders = sj_object_get_value(json, "borders");
	if (!borders) {
		slog("no borders for you");
	}
	count = sj_array_get_count(borders);
	for (int i = 0; i < count; i++) {
		bordert = sj_array_get_nth(borders, i);
		if (!bordert) continue;
		bord = border_new();
		if (!bord) {
			slog("couldn't create border");
			return;
		}
		min = sj_object_get_value(bordert, "min");
		if (!min) {
			slog("no min found");
		}
		sj_get_float_value(sj_array_get_nth(min, 0), &x);
		sj_get_float_value(sj_array_get_nth(min, 1), &y);
		slog("this works %f", y);
		slog("x = %f", x);
		bord->min = vector2d(x, y);
		max = sj_object_get_value(bordert, "max");
		sj_get_float_value(sj_array_get_nth(max, 0), &x);
		sj_get_float_value(sj_array_get_nth(max, 1), &y);
		slog("this works %f", y);
		slog("x = %f", x);
		bord->max = vector2d(x, y);
		sj_get_integer_value(sj_object_get_value(bordert, "type"), &type);
		bord->type = (borderType)type;

	}
	free(borders);
	
}


