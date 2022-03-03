#ifndef __BORDERS_H__
#define __BORDERS_H__

#include "gfc_matrix.h"

#include "entity.h"

typedef enum {

	BORDER_WALL,
	BORDER_TELEPORT


}borderType;

typedef struct {

	Uint8 inuse; //

	Vector2D min;
	Vector2D max;

	borderType type;

}border;


void borders_free(border *bord);

void borders_close();

void borders_init(Uint32 maxBorders);

border *border_new();

void borders_draw(border* bord);

void borders_draw_all();

void borders_update(Entity* self);

void borders_onCollide(Entity* ent, border *bord);


#endif