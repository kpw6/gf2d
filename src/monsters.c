#include "simple_logger.h"
#include "simple_json.h"

#include "gfc_audio.h"
#include "gfc_input.h"

#include "monsters.h"
#include "attacks.h"
#include "physics.h"


void monsters_think(Entity* self) {
	Entity* player;
	const Uint8* keys;

	player = entity_isPlayer();
	keys = SDL_GetKeyboardState(NULL);
	if (self->control) {
		monster_movement(self);
		if (gfc_input_command_released("retrieve")) {
			gfc_sound_play(gfc_sound_load("sounds/PokebReturn.mp3", 1, 0), 0, 1, -1, -1);
			player->control = 1;
			entity_free(self);

		}
		if (gfc_input_command_pressed("attack")) {
			attack_new("config/attacks.json", "bubble", vector2d(self->position.x + 40, self->position.y));
		}
	}
}

void monsters_ontouch(Entity* self, Entity* other) {
	pushback_entity(other, self);
}


Entity* monsters_new(char* filename, monsterType type, Vector2D position) {
	SJson* json, *monster;
	Entity* monsters;
	monsters = entity_new();
	if (!monsters) {
		slog("Cannot give a an Entity to monsters");
		return NULL;
	}
	json = sj_load(filename);
	if (!json) {
		slog("unknown filename for monsters");
		return NULL;
	}
	monsters->type = type;
	monsters->think = monsters_think;
	monsters->onTouch = monsters_ontouch;

	monsters->position = position;
	vector2d_add(monsters->min, monsters->position, vector2d(-10, -10));
	vector2d_add(monsters->max, monsters->position, vector2d(10, 10));

	switch (type) {
	case MONSTER_SQUIRTLE:
		monster = sj_object_get_value(json, "MONSTER_SQUIRTLE");
		monsters->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(monster, "image")), 32, 32, 3);
		if (!monsters->sprite) return NULL;
		break;
	case MONSTER_HOPPIP:
		monster = sj_object_get_value(json, "MONSTER_HOPPIP");
		monsters->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(monster, "image")), 64, 64, 3);
		if (!monsters->sprite) return NULL;
		break;
	}

	monsters->frame = 0;
	monsters->velocity = vector2d(1, 1);


	return monsters;
}