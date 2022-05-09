#include "simple_logger.h"
#include "simple_json.h"

#include "gfc_audio.h"
#include "gfc_input.h"


#include "AI.h"
#include "monsters.h"
#include "attacks.h"
#include "physics.h"


void monsters_think(Entity* self) {
	Entity* player;
	int a = gfc_random() * 100;
	player = entity_isPlayer();
	if (self->control) {
		monster_movement_playable(self);
		if (gfc_input_command_released("release")) {
			gfc_sound_play(gfc_sound_load("sounds/PokebReturn.mp3", 1, 0), 0, 1, -1, -1);
			player->control = 1;
			entity_free(self);

		}
		if (gfc_input_command_pressed("attack")) {
			attack_direction(self);
		}
	}
	else {
		if (a == 5) {
			attack_direction(self);
		}
		monster_movement_AI(self);
	}
}

void monsters_ontouch(Entity* self, Entity* other) {
	pushback_entity(other, self);
}


Entity* monsters_new(char* type) {
	SJson* json, *monster, *arr;
	Entity* monsters;
	float x, y;
	monsters = entity_new();

	if (!monsters) {
		slog("Cannot give a an Entity to monsters");
		return NULL;
	}
	json = sj_load("config/monsters.json");
	if (!json) {
		slog("unknown filename for monsters");
		return NULL;
	}
	monsters->think = monsters_think;
	monsters->onTouch = monsters_ontouch;

	if (strcmp(type, "MONSTER_SQUIRTLE") == 0) {
		monsters->mtype = MONSTER_SQUIRTLE;
		monster = sj_object_get_value(json, "MONSTER_SQUIRTLE");
		monsters->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(monster, "image")), 32, 32, 4);
		monsters->attackType = sj_get_string_value(sj_object_get_value(monster, "attack"));
		sj_get_integer_value(sj_object_get_value(monster, "health"), monsters->health);

		arr = sj_object_get_value(monster, "position");
		if (!arr) {
			slog("error getting monster position");
		}
		sj_get_float_value(sj_array_get_nth(arr, 0), &x);
		sj_get_float_value(sj_array_get_nth(arr, 1), &y);
		monsters->position = vector2d(x, y);
		slog("%f", x);
		slog("%f", y);
		vector2d_add(monsters->min, monsters->position, vector2d(-10, -10));
		vector2d_add(monsters->max, monsters->position, vector2d(10, 10));
		if (!monsters->sprite) return NULL;
	}

	if (strcmp(type, "MONSTER_HOPPIP") == 0) {
		slog("cap");
		monsters->mtype = MONSTER_HOPPIP;
		monster = sj_object_get_value(json, "MONSTER_HOPPIP");
		monsters->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(monster, "image")), 32, 32, 4);
		monsters->attackType = sj_get_string_value(sj_object_get_value(monster, "attack"));
		slog("%s", sj_get_string_value(sj_object_get_value(monster, "attack")));
		sj_get_integer_value(sj_object_get_value(monster, "health"), monsters->health);

		arr = sj_object_get_value(monster, "position");
		if (!arr) {
			slog("error getting monster position");
		}
		sj_get_float_value(sj_array_get_nth(arr, 0), &x);
		sj_get_float_value(sj_array_get_nth(arr, 1), &y);
		monsters->position.x = x;
		monsters->position.y = y;
		vector2d_add(monsters->min, monsters->position, vector2d(-10, -10));
		vector2d_add(monsters->max, monsters->position, vector2d(10, 10));

		slog("%s", monsters->sprite->filepath);

		if (!monsters->sprite) return NULL;
	}

	monsters->frame = 0;
	monsters->velocity = vector2d(1, 1);

	return monsters;
}