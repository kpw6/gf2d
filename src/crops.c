#include "simple_json.h"
#include "simple_logger.h"

#include "gfc_input.h"

#include "timer.h"

#include "crops.h"

static float f = 0;
static Uint32 ticks = 0;

void crops_think(Entity* crop) {
	if (!crop) return;
	if (ticks == 0) {
		ticks = SDL_GetTicks() + 10000;
	}
	if (crop->frame < 2) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), ticks)) {
			ticks = SDL_GetTicks() + 1000;
			crop->frame += 1;
		}
	}
}

void crops_ontouch(Entity* self, Entity* other) {
	const Uint8* keys;
	keys = SDL_GetKeyboardState(NULL);
	if (gfc_input_command_pressed("collect") && self->frame == 2) {
		entity_free(self);
	}
}
Entity* crops_new(char* filename, cropType type, Vector2D position) {

	SJson *json, *plant;
	Entity* crop;
	crop = entity_new();
	if (!crop) {
		slog("Cannot give a an Entity to crop");
		return NULL;
	}
	json = sj_load(filename);
	if (!json) {
		slog("unknown filename for crop");
		return NULL;
	}
	crop->type = type;
	crop->think = crops_think;
	crop->onTouch = crops_ontouch;

	crop->position = position;
	vector2d_add(crop->min, crop->position, vector2d(-20, -20));
	vector2d_add(crop->max, crop->position, vector2d(20, 20));

	switch (type) {
	case CROP_SQUIRTLE:
		plant = sj_object_get_value(json, "CROP_SQUIRTLE");
		crop->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(plant, "image")), 64, 64, 3);
		if (!crop->sprite) return NULL;
		break;
	case CROP_HOPPIP:
		plant = sj_object_get_value(json, "CROP_HOPPIP");
		crop->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(plant, "image")), 64, 64, 3);
		if (!crop->sprite) return NULL;
		break;
	case CROP_ORAN_BERRY:
		plant = sj_object_get_value(json, "CROP_ORAN_BERRY");
		crop->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(plant, "image")), 64, 64, 4);
		if (!crop->sprite) return NULL;
		break;
	}

	crop->frame = 0;


	return crop;


}