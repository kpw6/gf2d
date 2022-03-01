#include <SDL.H>

#include "simple_logger.h"
#include "simple_json.h"

#include "animations.h"
#include "physics.h"

#include "gfc_input.h"

#include "player.h"
#include "monsters.h"

#include "gf2d_sprite.h"
#include "gfc_audio.h"

void player_think(Entity* self) {
	Entity* monster;
	Vector2D mPosition;
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);
	
	if (!self) return;
	if (self->control) {
		player_movement(self);
		if (gfc_input_command_released("release")) {
			slog("button pressed");
			gfc_sound_play(gfc_sound_load("sounds/PokebOpen.mp3", 1, 0), 0, 1, -1, -1);
			self->control = 0;
			vector2d_add(mPosition, self->position, vector2d(100, 40));
			monster = monsters_new("config/entities.json", MONSTER_SQUIRTLE, mPosition);
			monster->control = 1;
	}

	}
}

void player_update(Entity* self) {
	if (!self) return;
}

void player_onTouch(Entity* self, Entity* other) {
	//pushback_entity(other, self);

}

Entity* player_new() {
	SJson *json, *ar;
	int width, height, count;
	float wspeed, rspeed;

	Entity* player = entity_new();
	if (!player) {
		slog("failed to make new player entity");
		return NULL;
	}
	
	json = sj_load("config/entities.json");
	if (!json) return;

	ar = sj_object_get_value(json, "player");
	if (!ar) {
		sj_free(json);
		return;
	}

	sj_get_integer_value(sj_object_get_value(ar, "width"), &width);
	sj_get_integer_value(sj_object_get_value(ar, "height"), &height);
	sj_get_integer_value(sj_object_get_value(ar, "count"), &count);
	sj_get_float_value(sj_object_get_value(ar, "walkspeed"), &wspeed);

	player->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(ar, "image")), width, height, count);
	if (!player->sprite) {
		slog("Failed to assign sprite to player");
	}


	player->control = 1;
	player->velocity = vector2d(wspeed, wspeed);
	player->position = vector2d(100, 100);
	vector2d_add(player->min, player->position, vector2d(-20, -20));
	vector2d_add(player->max, player->position, vector2d(20, 20));
	//player->radius = 1;
	player->frame = 0;
	player->think = player_think;
	player->update = player_update;
	player->onTouch = player_onTouch;

	player->isPlayer = 1;

	slog("%i walk speed", width);

	sj_free(json);

	return player;
}

