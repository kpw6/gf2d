#include "simple_json.h"
#include "simple_logger.h"

#include "player.h"
#include "monsters.h"
#include "enemy.h"

#include "physics.h"

#include "level.h"
#include "borders.h"
#include "gfc_audio.h"

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

	level_entity_load(json);
	lev->music = gfc_sound_load(sj_get_string_value(sj_object_get_value(json, "music")), 1, 1);
	gfc_sound_play(lev->music, 500, 1, -1, -1);

	sj_get_integer_value(sj_object_get_value(json, "plantAccess"), lev->plantAccess);
	
	lev->inuse = 1;
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

void level_draw() {
	gf2d_sprite_draw_image(currentLevel->image, vector2d(0, 0));
	entity_draw_all();
	borders_draw_all();

}

void level_load_borders(SJson* json) {
	SJson* borders, *bordert, *min, *max, *position;
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
		bord->min = vector2d(x, y);
		max = sj_object_get_value(bordert, "max");
		sj_get_float_value(sj_array_get_nth(max, 0), &x);
		sj_get_float_value(sj_array_get_nth(max, 1), &y);
		bord->max = vector2d(x, y);
		sj_get_integer_value(sj_object_get_value(bordert, "type"), &type);
		bord->type = (borderType)type;
		if (bord->type == 1){
			bord->filename = sj_get_string_value(sj_object_get_value(bordert, "level"));
			sj_get_float_value(sj_object_get_value(bordert, "positionx"), &bord->teleposition.x);
		}
		

	}
	free(borders);
	
}

void level_update() {
	entity_think_all();
	entity_update_all();
	entity_collision_tests();
}

void level_entity_load(SJson* json) {
	SJson* entities, *jentity;
	char *entity;
	char sub[6];
	int count;

	if (!json) return;


	entities = sj_object_get_value(json, "entities");
	count = sj_array_get_count(entities);
	for (int i = 0; i < count-1; i++) {
		entity = sj_get_string_value(sj_array_get_nth(entities, i));
		if (strcmp(&entity, "player")) {
			if (!entity_check_if_player()) {
				player_new();
			}
		}
		strncpy(sub, &entity, 6);
		if (strcmp(sub, "MONSTER")) {
			monsters_new(entity);
		}
	}
	slog("end");
	free(entities);

}

void level_unload() {
	entity_free_all();
	border_free_all();
}

void level_switch(char* filename, border *bord) {
	Entity* ent = entity_isPlayer();
	level_unload();
	gfc_sound_clear_all();
	level_free(currentLevel);
	currentLevel = level_load(filename);
	entity_teleport(ent, vector2d(bord->teleposition.x, ent->position.y));
}


