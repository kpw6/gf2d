#include <SDL.H>

#include "simple_logger.h"

#include "animations.h"

#include "enemy.h"
#include "gf2d_sprite.h"

static int lastPress = 0;

void enemy_think(Entity* self) {


}

void enemy_update(Entity* self) {
	if (!self) return;
}

void enemy_onTouch(Entity* self, Entity* other) {
	vector2d_add(other->position, other->position, vector2d(-1, 0));
	vector2d_add(other->min, other->position, vector2d(-1, 0));
	vector2d_add(other->max, other->position, vector2d(-1, 0));
	slog("%i is this position", self->position.x);
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
	vector2d_add(enemy->min, enemy->position, vector2d(-45, -45));
	vector2d_add(enemy->max, enemy->position, vector2d(45, 45));
	enemy->frame = 0;
	enemy->think = enemy_think;
	enemy->update = enemy_update;
	enemy->onTouch = enemy_onTouch;

	return enemy;
}

