#include "simple_logger.h"

#include "borders.h"

#include "gf2d_draw.h"

#include "physics.h"

#include "level.h"

typedef struct {

	border* border_list;
	Uint32 border_count;

}bordersManager;

static bordersManager BM = { 0 };

void borders_close() {
	int i;
	for (i = 0; i < BM.border_count; i++) {
		borders_free(&BM.border_list[i]);
	}
	free(BM.border_list);
	slog("Border manager closed");
}

void borders_init(Uint32 maxBorders) {
	if (maxBorders <= 0) {
		slog("not enough levels to create");
		return;
	}
	BM.border_list = (border*)gfc_allocate_array(sizeof(border), maxBorders);
	if (!BM.border_list) return;
	BM.border_count = maxBorders;
	atexit(borders_close);
	slog("Border Manager Initilialzed");
}

void borders_free(border *bord) {
	if (!bord)return;
	memset(bord, 0, sizeof(border));
}

border *border_new() {
	for (int i = 0; i < BM.border_count; i++) {
		if (!BM.border_list[i].inuse) {
			BM.border_list[i].inuse = 1;
			return &BM.border_list[i];
		}
	}
	slog("out of memory for borders");
	return NULL;
}

void borders_draw(border* bord) {
	SDL_Rect hitbox;
	gf2d_draw_line(bord->max, bord->min, vector4d(20, 50, 100, 10));
}

void borders_draw_all() {
	for (int i = 0; i < BM.border_count; i++) {
		if (BM.border_list[i].inuse) {
			borders_draw(&BM.border_list[i]);
		}
	}
}

void borders_update(Entity* ent) {
	if (!ent) return;
	for (int i = 0; i < BM.border_count; i++) {
		if (BM.border_list[i].inuse) {
			if (ent_border_collision(ent, &BM.border_list[i])) {
				borders_onCollide(ent, &BM.border_list[i]);
			}
			continue;
		}
		continue;
	}
}


void borders_onCollide(Entity* ent, border* bord) {
	if (!ent) return;
	if (!bord)return;
	switch (bord->type) {
		case BORDER_WALL:
			pushback_entity_on_border(ent, bord);
			break;
		case BORDER_TELEPORT:
			slog("what");
			if(ent->isPlayer) {
				slog("hello");
				slog("Border touched: %s", bord->filename);
				level_switch(bord->filename, bord);
			}
			break;
	}
}

void border_free_all(border* bord) {
	for (int i = 0; i < BM.border_count; i++) {
		if (BM.border_list[i].inuse && &BM.border_list[i] != bord) {
			borders_free(&BM.border_list[i]);
		}
	}
}
