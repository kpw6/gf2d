#include "attacks.h"

#include "simple_json.h"
#include "simple_logger.h"

#include "physics.h"

void attack_think(Entity* self) {
	switch (self->direction) {
	case 0:
		simple_movement(self, self->velocity.x, 0);
		break;
	case 1:
		simple_movement(self, -self->velocity.x, 0);
		break;
	case 2:
		simple_movement(self, 0, self->velocity.y);
		break;
	case 3:
		simple_movement(self, 0, -self->velocity.y);
		break;
	}
	if (self->lifeSpan > 10) {
		entity_free(self);
	}
	self->lifeSpan += .1;
	if (self->frame < 1.99) {
		self->frame += .1;
	}
	else {
		self->frame = 0;
	}
}

void attack_onTouch(Entity* self, Entity* other) {
	other->health = other->health - self->damage;
	slog("health: %i", other->health);
	entity_free(self);
	if (other->health <= 0) entity_free(other);
}

Entity* attack_new(char* filename, char *type, Vector2D position) {
	SJson* json, *at;
	int width, height, frames;
	float speed;
	Entity* ent;
	ent = entity_new();
	if (!ent) {
		slog("failed to make new attack");
		return NULL;
	}
	if (!filename) {
		slog("No attack file given");
		return NULL;
	}
	if (!type) {
		slog("No attack type given");
		return NULL;
	}
	json = sj_load(filename);
	if (!json) {
		slog("Unknown file for attack");
		return NULL;
	}
	at = sj_object_get_value(json, type);
	if (!at) {
		slog("failed to load type");
		return NULL;
	}
	
	sj_get_integer_value(sj_object_get_value(at, "width"), &width);
	sj_get_integer_value(sj_object_get_value(at, "height"), &height);
	sj_get_integer_value(sj_object_get_value(at, "frames"), &frames);

	sj_get_float_value(sj_object_get_value(at, "speed"), &speed);
	ent->velocity = vector2d(speed, speed);

	ent->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(at, "image")), width, height, frames);
	if (!ent->sprite) {
		slog("Failed to load attack sprite");
		return NULL;
	}

	sj_get_integer_value(sj_object_get_value(at, "damage"), &ent->damage);

	ent->position = position;

	ent->lifeSpan = 0;

	vector2d_add(ent->min, ent->position, vector2d(-10, -10));
	vector2d_add(ent->max, ent->position, vector2d(10, 10));

	ent->think = attack_think;
	ent->onTouch = attack_onTouch;

	return ent;
}

void attack_direction(Entity* self) {
	Entity* ent;
	if (!self) return;
	switch (lastPress) {
	case 0:
		ent = attack_new("config/attacks.json", self->attackType, vector2d(self->position.x + 40, self->position.y));
		ent->direction = 0;
		break;
	case 1:
		ent = attack_new("config/attacks.json", self->attackType, vector2d(self->position.x - 40, self->position.y));
		ent->direction = 1;
		break;
	case 2:
		ent = attack_new("config/attacks.json", self->attackType, vector2d(self->position.x, self->position.y + 40));
		ent->direction = 2;
		break;
	case 3:
		ent = attack_new("config/attacks.json", self->attackType, vector2d(self->position.x, self->position.y - 40));
		ent->direction = 3;
		break;
	}

}