#include "button.h"
#include "gf2d_draw.h"
#include "gfc_input.h"
#include "menus.h"

#include "simple_logger.h"

button* button_new(buttonType type, Vector2D position, SDL_Rect rect, Sprite* image) {
	button* but = NULL;
	but->type = type;
	but->position = position;
	but->border = rect;
	but->image = image;

	return but;
}

void button_draw(button* but) {
	gf2d_sprite_draw(but->image, but->position, NULL, NULL, NULL, NULL, NULL, 0);
	if (but->hovered) {
		gf2d_draw_rect(but->border, vector4d(0, 0, 0, 0));
	}
}

void button_action(button* but) {
	switch (but->type) {
	case EXIT:
		if (gfc_input_command_pressed("enter")) {

		}
		break;
	case BUY:
		if (gfc_input_command_pressed("enter")) {

		}
		break;
	case SELL:
		break;
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