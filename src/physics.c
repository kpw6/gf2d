#include "entity.h"
#include "animations.h"
#include "borders.h"

static int lastPress = 0; //This just to remember the place for animation

void simple_movement(Entity* self, float speedx, float speedy) {
    vector2d_add(self->position, self->position, vector2d(speedx, speedy));
    self->min.x += speedx;
    self->max.x += speedx;
    self->min.y += speedy;
    self->max.y += speedy;
}

void pushback_entity(Entity* self, Entity* other) {
	if (other->min.x < self->max.x) {
		simple_movement(other, -other->velocity.x, 0);
	}
	if (other->max.x > self->min.x) {
		simple_movement(other, other->velocity.x, 0);
	}
	if (other->max.y > self->min.y) {
		simple_movement(other, 0, other->velocity.y);
	}
	if (other->min.y < self->max.y) {
		simple_movement(other, 0, -other->velocity.y);
	}
}

void pushback_entity_on_border(Entity* self, border* bord) {
	if (self->min.x < bord->max.x) {
		simple_movement(self, -self->velocity.x, 0);
	}
	if (self->max.x > bord->min.x) {
		simple_movement(self, self->velocity.x, 0);
	}
	if (self->max.y > bord->min.y) {
		simple_movement(self, 0, self->velocity.y);
	}
	if (self->min.y < bord->max.y) {
		simple_movement(self, 0, -self->velocity.y);
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

void monster_movement(Entity* self) {
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

Uint8 ent_rect_collision(Entity* self, Entity* other) {
    return (self->min.x <= other->max.x && self->max.x >= other->min.x) &&
        (self->min.y <= other->max.y && self->max.y >= other->min.y);
}

Uint8 ent_circ_collision(Entity* self, Entity* other) {

	//return (vector2d_magnitude_squared(vector2d(A.x - B.x, A.y - B.y), vector2d(A.r);
}

Uint8 ent_border_collision(Entity * self, border *other) {
	return (self->min.x <= other->max.x && self->max.x >= other->min.x) &&
			(self->min.y <= other->max.y && self->max.y >= other->min.y);
}