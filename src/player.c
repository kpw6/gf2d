#include <SDL.H>

#include "simple_logger.h"

#include "animations.h"

#include "player.h"
#include "gf2d_sprite.h"

static int lastPress = 0;

void player_think(Entity* self) {

	if (!self) return;
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_RIGHT]) {

		player_animation_movement(self, lastPress);

		vector2d_add(self->position, self->position, vector2d(1, 0));
		vector2d_add(self->min, self->position, vector2d(1, 0));
		vector2d_add(self->max, self->position, vector2d(1, 0));
		lastPress = 0;
	}
	else if (keys[SDL_SCANCODE_LEFT]) {

		player_animation_movement(self, lastPress);

		vector2d_add(self->position, self->position, vector2d(-1, 0));
		vector2d_add(self->min, self->position, vector2d(-1, 0));
		vector2d_add(self->max, self->position, vector2d(-1, 0));
		lastPress = 1;
	}
	else if (keys[SDL_SCANCODE_DOWN]) {

		player_animation_movement(self, lastPress);

		vector2d_add(self->position, self->position, vector2d(0, 1));
		vector2d_add(self->min, self->position, vector2d(0, 1));
		vector2d_add(self->max, self->position, vector2d(0, 1));
		lastPress = 2;
	}
	else if (keys[SDL_SCANCODE_UP]) {

		player_animation_movement(self, lastPress);

		vector2d_add(self->position, self->position, vector2d(0, -1));
		vector2d_add(self->min, self->position, vector2d(0, -1));
		vector2d_add(self->max, self->position, vector2d(0, -1));
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
	slog("running");
}

Entity* player_new() {

	Entity* player = entity_new();
	if (!player) {
		slog("failed to make new player entity");
		return NULL;
	}
	player->sprite = gf2d_sprite_load_all("images/trainer.png", 64, 64, 4);
	if (!player->sprite) {
		slog("Failed to assign sprite to player");
	}
	player->position = vector2d(100, 100);
	vector2d_add(player->min, player->position, vector2d(-45, -45));
	vector2d_add(player->max, player->position, vector2d(45, 45));
	player->frame = 0;
	player->think = player_think;
	player->update = player_update;
	player->onTouch = player_onTouch;

	return player;
}

