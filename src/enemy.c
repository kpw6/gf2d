#include <SDL.H>

#include "simple_logger.h"

#include "animations.h"
#include "physics.h"

#include "enemy.h"
#include "gf2d_sprite.h"

static int lastPress = 0;

void enemy_think(Entity* self) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_h:
			if (self->active) self->active = 0;
			else self->active = 1;
			break;
		}
	default:
		break;
	}
}

}

void enemy_update(Entity* self) {
	if (!self) return;
}

void enemy_onTouch(Entity* self, Entity* other) {
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);
	pushback_entity(self, other);
	if (keys[SDL_SCANCODE_A]) {
		slog("a was pressed");
	}

	
	
}


Entity* enemy_new() {

	Entity* enemy = entity_new();
	if (!enemy) {
		slog("failed to make new player entity");
		return NULL;
	}
	enemy->sprite = gf2d_sprite_load_all("images/trainer.png", 64, 64, 4);
	if (!enemy->sprite) {
		slog("Failed to assign sprite to player");
	}
	enemy->position = vector2d(300, 300);
	vector2d_add(enemy->min, enemy->position, vector2d(-10, -10));
	vector2d_add(enemy->max, enemy->position, vector2d(10, 10));
	//enemy->radius = 1;
	enemy->frame = 0;
	enemy->think = enemy_think;
	enemy->update = enemy_update;
	enemy->onTouch = enemy_onTouch;

	return enemy;
}

