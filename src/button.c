#include "button.h"
#include "gf2d_draw.h"
#include "gfc_input.h"

#include "simple_logger.h"


void button_draw(button* but) {
	gf2d_sprite_draw(but->image, but->position, NULL, NULL, NULL, NULL, NULL, 0);
	if (but->hovered) {
		gf2d_draw_rect(but->border, vector4d(1, 3, 5, 2));
	}
}


void button_free(button* but) {
	if (!but) {
		slog("No entity to free");
		return;
	}
	if (but->image) {
		gf2d_sprite_free(but->image);
	}
	memset(but, 0, sizeof(but));
}