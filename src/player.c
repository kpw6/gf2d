#include <SDL.H>

#include "simple_logger.h"
#include "simple_json.h"

#include "animations.h"
#include "physics.h"

#include "player.h"
#include "gf2d_sprite.h"

static int lastPress = 0;

void player_think(Entity* self) {

	if (!self) return;
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_RIGHT]) {

		player_animation_movement(self, lastPress);

		simple_movement(self, self->velocity.x, 0);
		lastPress = 0;
	}
	else if (keys[SDL_SCANCODE_LEFT]) {

		player_animation_movement(self, lastPress);

		simple_movement(self, -self->velocity.x, 0);
		lastPress = 1;
	}
	else if (keys[SDL_SCANCODE_DOWN]) {

		player_animation_movement(self, lastPress);

		simple_movement(self, 0, self->velocity.y);
		lastPress = 2;
	}
	else if (keys[SDL_SCANCODE_UP]) {

		player_animation_movement(self, lastPress);

		simple_movement(self, 0, -self->velocity.y);
		lastPress = 3;
	}
	else {
		player_animation_return_idle(self, lastPress);
	}
}

void player_update(Entity* self) {
	if (!self) return;
}

void player_onTouch(Entity* self) {
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

	player->velocity = vector2d(wspeed, wspeed);
	player->position = vector2d(100, 100);
	vector2d_add(player->min, player->position, vector2d(-20, -20));
	vector2d_add(player->max, player->position, vector2d(20, 20));
	player->frame = 0;
	player->think = player_think;
	player->update = player_update;
	//player->onTouch = player_onTouch;

	slog("%i walk speed", width);

	sj_free(json);

	return player;
}

