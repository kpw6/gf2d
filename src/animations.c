#include "animations.h"

void player_animation_movement(Entity* self) {
	if (!self) return;

	switch (self->lastMovement) {
	case 0:

		if (self->frame < 9) self->frame = 9;
		self->frame += .1;
		if (self->frame >= 11) self->frame = 9;

		break;
	case 1:

		if (self->frame < 5) self->frame = 5;
		self->frame += .1;
		if (self->frame >= 8) self->frame = 5;

		break;
	case 2:

		self->frame += .1;
		if (self->frame >= 4) self->frame = 0;

		break;
	case 3:

		if (self->frame < 12) self->frame = 12;
		self->frame += .1;
		if (self->frame >= 16) self->frame = 12;

		break;
	}

}

void player_animation_return_idle(Entity* self) {
	switch (self->lastMovement) {
	case 0:
		self->frame = 8;
		break;
	case 1:
		self->frame = 4;
		break;
	case 2:
		self->frame = 0;
		break;
	case 3:
		self->frame = 12;
		break;
	}
}

void monster_animation_movement(Entity* self) {
	if (!self) return;

	switch (self->lastMovement) {
	case 0:

		if (self->frame < 6) self->frame = 6;
		self->frame += .1;
		if (self->frame >= 8) self->frame = 6;

		break;
	case 1:

		if (self->frame < 3) self->frame = 3;
		self->frame += .1;
		if (self->frame >= 6) self->frame = 3;

		break;
	case 2:

		self->frame += .1;
		if (self->frame >= 3) self->frame = 0;

		break;
	case 3:

		if (self->frame < 9) self->frame = 9;
		self->frame += .1;
		if (self->frame >= 11) self->frame = 9;

		break;
	}

}

void monster_animation_return_idle(Entity* self) {
	switch (self->lastMovement) {
	case 0:
		self->frame = 6;
		break;
	case 1:
		self->frame = 3;
		break;
	case 2:
		self->frame = 0;
		break;
	case 3:
		self->frame = 9;
		break;
	}
}