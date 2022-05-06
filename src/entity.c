#include "entity.h"
#include "gf2d_sprite.h"
#include "physics.h"
#include "gf2d_draw.h"

#include "simple_logger.h"

typedef struct  {

	Entity* entity_list; //list of entities
	Uint64	entity_count; //count for the entity list

}entityManager;

static entityManager entity_manager = { 0 };

void entity_system_close() {
	int i;
	for (i = 0; i < entity_manager.entity_count; i++) {
		entity_free(&entity_manager.entity_list[i]);
	}
	free(entity_manager.entity_list);
	slog("Entity system closed");
}

void entity_system_init(Uint32 maxEntities) {
	entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), maxEntities);
	if (entity_manager.entity_list == NULL) {
		slog("failed to allocate array in entity_list");
		return;
	}
	entity_manager.entity_count = maxEntities;
	atexit(entity_system_close);
	slog("Entity system initialzed successfully");
}

Entity* entity_new() {
	int i;
	for (i = 0; i < entity_manager.entity_count; i++) {
		if (!entity_manager.entity_list[i].inuse) {
			entity_manager.entity_list[i].inuse = 1;
			entity_manager.entity_list[i].scale.x = 1;
			entity_manager.entity_list[i].scale.y = 1;
			entity_manager.entity_list[i].min = vector2d(0,0);
			entity_manager.entity_list[i].max = vector2d(0,0);
			entity_manager.entity_list[i].active = 1;
			return (&entity_manager.entity_list[i]);
		}
	}
	slog("no space free for new entity");
	return NULL;
}

void entity_draw(Entity* self) {
	SDL_Rect hitbox, external;
	if (!self) return;
	if (!self->sprite) return;
	gf2d_sprite_draw(self->sprite, self->position, &self->scale, NULL, NULL, NULL, NULL, self->frame);
	hitbox.x = self->max.x - 10;
	hitbox.y = self->max.y;
	hitbox.w = self->max.x - self->min.x;
	hitbox.h = self->max.y - self->min.y;
	gf2d_draw_rect(hitbox, vector4d(43, 52, 70, 255));
	if (self->cmax.x != 0) {
		external.x = self->cmax.x - 10;
		external.y = self->cmax.y;
		external.w = self->cmax.x - self->cmin.x;
		external.h = self->cmax.y - self->cmin.y;
		gf2d_draw_rect(external, vector4d(43, 52, 70, 255));
	}
	
}

void entity_draw_all() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].active) {
			entity_draw(&entity_manager.entity_list[i]);
		}
	}
}

void entity_free(Entity* self) {
	if (!self) {
		slog("No entity to free");
		return;
	}
	if (self->sprite) {
		gf2d_sprite_free(self->sprite);
	}
	memset(self, 0, sizeof(self));
}

void entity_think(Entity* self) {
	if (!self) return;
	if (self->think) self->think(self);
}

void entity_think_all() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].inuse) {
			entity_think(&entity_manager.entity_list[i]);
		}
	}
}

void entity_update(Entity* self) {
	if (!self) return;
	if (self->update) self->update(self);
}

void entity_update_all() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].inuse) {
			entity_update(&entity_manager.entity_list[i]);
		}
	}
}

void entity_onTouch(Entity* self, Entity* other) {
	if (!self) return;
	if (!other) return;
	if (self->onTouch) self->onTouch(self, other);
	if (other->onTouch) other->onTouch(other, self);
}

void entity_collision_tests() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		for (int j = entity_manager.entity_count; j > 0; j--) {
			if (entity_manager.entity_list[i].active && entity_manager.entity_list[j].active && j != i) {
				
				if (ent_rect_collision(&entity_manager.entity_list[i], &entity_manager.entity_list[j])) {
					entity_onTouch(&entity_manager.entity_list[i], &entity_manager.entity_list[j]);
				}
				if (ent_crect_collision(&entity_manager.entity_list[i], &entity_manager.entity_list[j])) {

					entity_menu_open(&entity_manager.entity_list[i], &entity_manager.entity_list[j]);
				}
				continue;
			}
			continue;
		}
	}
}
Entity* entity_isPlayer() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].isPlayer) {
			return &entity_manager.entity_list[i];
		}
	}
	slog("Player doesn't exist");
	return NULL;
}

void entity_layer_sort() {
	Entity temp;
	for (int i = 0; i < entity_manager.entity_count; i++) {
		for (int j = 0; j < entity_manager.entity_count - i - 1; j++) {
			if (entity_manager.entity_list[j].position.y > entity_manager.entity_list[j+1].position.y) {
				temp = entity_manager.entity_list[j];
				entity_manager.entity_list[j] = entity_manager.entity_list[j + 1];
				entity_manager.entity_list[j + 1] = temp;
			}
			continue;
		}
	}
}

void entity_menu_open(Entity* self, Entity* other) {
	if (!self) return;
	if (!other) return;
	if (self->menuOpen) self->menuOpen(self);
	if (other->menuOpen) other->menuOpen(other);
}

void entity_free_all() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].inuse && !entity_manager.entity_list[i].isPlayer) {
			entity_free(&entity_manager.entity_list[i]);
		}
	}
}

Uint8 entity_check_if_player() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].isPlayer) {
			return 1;
		}
	}
	slog("Player doesn't exist");
	return 0;
}