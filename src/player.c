#include <SDL.H>

#include "simple_logger.h"

#include "player.h"
#include "gf2d_sprite.h"

void player_think(Entity* self);

Entity* player_new() {

	Entity* player = entity_new();
	if (!player) {
		slog("failed to make new player entity");
		return;
	}
	player->sprite = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	player->position = vector2d(100, 100);
	player->think = player_think;
}

void player_think(Entity* self) {
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_RIGHT]) vector2d_add(self->position, self->position, vector2d(1,0));
	if (keys[SDL_SCANCODE_LEFT]) vector2d_add(self->position, self->position, vector2d(-1, 0));
	if (keys[SDL_SCANCODE_DOWN]) vector2d_add(self->position, self->position, vector2d(0, 1));
	if (keys[SDL_SCANCODE_UP]) vector2d_add(self->position, self->position, vector2d(0, -1));


}