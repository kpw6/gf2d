#include "entity.h"
#include "gf2d_sprite.h"

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
			return (&entity_manager.entity_list[i]);
		}
	}
	slog("no space free for new entity");
	return;
}

void entity_draw(Entity* self) {
	if (!self) return;
	if (!self->sprite) return;
	gf2d_sprite_draw(self->sprite, self->position, NULL, NULL, NULL, NULL, NULL, self->frame);
}

void entity_draw_all() {
	for (int i = 0; i < entity_manager.entity_count; i++) {
		if (entity_manager.entity_list[i].inuse) {
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