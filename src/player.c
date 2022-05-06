#include <SDL.H>

#include "simple_logger.h"
#include "simple_json.h"

#include "animations.h"
#include "physics.h"
#include "timer.h"

#include "gfc_input.h"

#include "player.h"
#include "monsters.h"
#include "borders.h"
#include "menus.h"
#include "crops.h"
#include "level.h"

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
			gfc_sound_play(gfc_sound_load("sounds/PokebOpen.mp3", 1, 0), 0, 1, -1, -1);
		}
		if (gfc_input_command_pressed("plant")) {
			if (currentLevel->plantAccess) {
				crops_new("config/crops.json", CROP_SQUIRTLE, self->position);
			}
		}
	}
}
void player_update(Entity* self) {
	if (!self) return;
	borders_update(self);
	if (self->health < 0) entity_free(self);
}


Entity* player_new() {
	SJson *json, *ar;
	int width, height, count;
	float wspeed;

	Entity* player = entity_new();
	if (!player) {
		slog("failed to make new player entity");
	}
	
	json = sj_load("config/player.json");
	if (!json) {
		slog("player file not found");
	}

	ar = sj_object_get_value(json, "player");
	if (!ar) {
		slog("no player in player file");
	}

	sj_get_integer_value(sj_object_get_value(ar, "width"), &width);
	sj_get_integer_value(sj_object_get_value(ar, "height"), &height);
	sj_get_integer_value(sj_object_get_value(ar, "count"), &count);
	sj_get_float_value(sj_object_get_value(ar, "walkspeed"), &wspeed);

	player->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(ar, "image")), width, height, count);
	slog("image: &s", player->sprite);
	if (!player->sprite) {
		slog("Failed to assign sprite to player");
	}

	sj_get_integer_value(sj_object_get_value(ar, "health"), &player->health);


	player->control = 1;
	player->velocity = vector2d(wspeed, wspeed);
	player->position = vector2d(100, 200);
	vector2d_add(player->min, player->position, vector2d(-20, -20));
	vector2d_add(player->max, player->position, vector2d(20, 20));
	player->frame = 0;
	player->think = player_think;
	player->update = player_update;

	player->isPlayer = 1;

	sj_free(json);

	return player;
}

