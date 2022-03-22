#include "physics.h"
#include "entity.h"
#include "animations.h"
#include "borders.h"
#include "timer.h"

#include "simple_logger.h"

lastPress = 0;

void simple_movement(Entity* self, float speedx, float speedy) {
    vector2d_add(self->position, self->position, vector2d(speedx * deltaTime, speedy * deltaTime));
	self->min.x += speedx * deltaTime;
	self->max.x += speedx * deltaTime;
	self->min.y += speedy * deltaTime;
	self->max.y += speedy * deltaTime;
}

void pushback_entity(Entity* self, Entity* other) {
	if (other->min.x < self->max.x && lastPress == 0) {
		simple_movement(other, -other->velocity.x, 0);
	}
	if (other->max.x > self->min.x && lastPress == 1) {
		simple_movement(other, other->velocity.x, 0);
	}
	if (other->max.y > self->min.y && lastPress == 3) {
		simple_movement(other, 0, other->velocity.y);
	}
	if (other->min.y < self->max.y && lastPress == 2) {
		simple_movement(other, 0, -other->velocity.y);
	}
}

void pushback_entity_on_border(Entity* self, border* bord) {
	if (self->min.x < bord->max.x && lastPress == 0) {
		simple_movement(self, -self->velocity.x, 0);
	}
	if (self->max.x > bord->min.x && lastPress == 1) {
		simple_movement(self, self->velocity.x, 0);
	}
	if (self->max.y > bord->min.y && lastPress == 3) {
		simple_movement(self, 0, self->velocity.y);
	}
	if (self->min.y < bord->max.y && lastPress == 2) {
		simple_movement(self, 0, -self->velocity.y);
		slog("Velocity %f", -self->velocity.y);
	}
}

void player_movement(Entity* self) {
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

void monster_movement_playable(Entity* self) {
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_RIGHT]) {

		monster_animation_movement(self, lastPress);

		simple_movement(self, self->velocity.x, 0);
		lastPress = 0;
	}
	else if (keys[SDL_SCANCODE_LEFT]) {

		monster_animation_movement(self, lastPress);

		simple_movement(self, -self->velocity.x, 0);
		lastPress = 1;
	}
	else if (keys[SDL_SCANCODE_DOWN]) {

		monster_animation_movement(self, lastPress);

		simple_movement(self, 0, self->velocity.y);
		lastPress = 2;
	}
	else if (keys[SDL_SCANCODE_UP]) {

		monster_animation_movement(self, lastPress);

		simple_movement(self, 0, -self->velocity.y);
		lastPress = 3;
	}
	else {
		monster_animation_return_idle(self, lastPress);
	}
}

void monster_movement(Entity* self, int c) {
	switch (c) {
	case 0:
		monster_animation_movement(self, c);

		simple_movement(self, self->velocity.x, 0);
		break;
	case 1:
		monster_animation_movement(self, c);

		simple_movement(self, -self->velocity.x, 0);
		break;
	case 2:
		monster_animation_movement(self, c);

		simple_movement(self, 0, self->velocity.y);
		break;
	case 3:
		monster_animation_movement(self, c);

		simple_movement(self, 0, -self->velocity.y);
		break;
	}
}

Uint8 ent_rect_collision(Entity* self, Entity* other) {
    return (self->min.x <= other->max.x && self->max.x >= other->min.x) &&
        (self->min.y <= other->max.y && self->max.y >= other->min.y);
}


Uint8 ent_border_collision(Entity * self, border *other) {
	return (self->min.x <= other->max.x && self->max.x >= other->min.x) &&
			(self->min.y <= other->max.y && self->max.y >= other->min.y);
}