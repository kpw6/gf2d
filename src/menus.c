#include "menus.h"

#include "gfc_input.h"

#include "simple_logger.h"
#include "simple_json.h"


typedef struct {

	menu* menu_list;
	Uint32 menu_count;

}menuManager;

static menuManager menu_manager = { 0 };

void menu_manager_close() {
	int i;
	for (i = 0; i < menu_manager.menu_count; i++) {
		menu_free(&menu_manager.menu_list[i]);
	}
	free(menu_manager.menu_list);
	slog("Menu system closed");
}

void menu_manager_init(Uint32 maxMenus) {
	menu_manager.menu_list = gfc_allocate_array(sizeof(menu), maxMenus);
	if (menu_manager.menu_list == NULL) {
		slog("failed to allocate array in entity_list");
		return;
	}
	menu_manager.menu_count = maxMenus;
	atexit(menu_manager_close);
	slog("Menu system initialzed successfully");
}

menu* menu_load(char* filename, char* menuChoice) {
	menu* men;
	SJson* json, *menu, *buttons, *position;
	float x, y;
	char* border = "", * message = "";


	men	= menu_new();
	if (!men) return NULL;

	json = sj_load(filename);
	if (!json) return NULL;
	
	menu = sj_object_get_value(json, menuChoice);
	if (!men) {
		slog("menu choice is not an option");
		return NULL;
	}

	buttons = sj_object_get_value(menu, "buttons");
	if (!buttons) {
		slog("buttons don't exist");
		return NULL;
	}
	
	menu_button_load(men, buttons);

	position = sj_object_get_value(menu, "position");
	sj_get_float_value(sj_array_get_nth(position, 0), &x);
	slog("border x position: %f", x);
	sj_get_float_value(sj_array_get_nth(position, 1), &y);

	men->position = vector2d(x, y);
	
	sj_get_string_value(sj_object_get_value(menu, "border"), border);
	men->border = gf2d_sprite_load_all(border, 100, 180, 0);
	slog("border sprite: %s", men->border);
	if (!men->border) {
		slog("menu border cannot be loaded");

	}

	men->current_button = 0;
	free(json);
	return men;
}


menu* menu_new() {
	int i;
	for (i = 0; i < menu_manager.menu_count; i++) {
		if (!menu_manager.menu_list[i].inuse) {
			menu_manager.menu_list[i].inuse = 1;
			return (&menu_manager.menu_list[i]);
		}
	}
	slog("no space free for new entity");
	return NULL;
}

button* menu_button_new(menu* men) {
	if (!men) return NULL;
	if (!men->button_list)
	{
		slog("menu doesn't have a button list for new");
		return NULL;
	}
	int i;
	for (i = 0; i < men->buttons_count; i++) {
		if (!men->button_list[i].inuse) {
			men->button_list[i].inuse = 1;
			return (&men->button_list[i].inuse);
		}
	}
	slog("no space free for new button");
	return NULL;
}

void menu_button_load(menu* men, SJson* buttons) {
	SJson* sbutton, * position;
	char* bimage = "", message = "";
	button* but;
	float x, y;

	men->buttons_count = sj_array_get_count(buttons);

	men->button_list = (button*)gfc_allocate_array(sizeof(button), men->buttons_count);

	slog("here?");

	for (int i = 0; i < men->buttons_count; i++) {
		sbutton = sj_array_get_nth(buttons, i);
		but = menu_button_new(men);

		sj_get_integer_value(sj_object_get_value(sbutton, "type"), &(buttonType)but->type);
		if (but->type < 0) {
			slog("failed to give button a type");
			return NULL;
		}
		sj_get_string_value(sj_object_get_value(sbutton, "message"), message);
		but->message = message;
		if (!but->message) {
			slog("failed to give button a message");
			continue;
		}
		position = sj_object_get_value(sbutton, "position");
		sj_get_float_value(sj_array_get_nth(position, 0), &x);
		sj_get_float_value(sj_array_get_nth(position, 1), &y);
		but->position = vector2d(x, y);
		sj_get_string_value(sj_object_get_value(sbutton, "image"), bimage);
		but->image = gf2d_sprite_load_all(bimage, 80, 20, 0);
		if (!but->image) {
			slog("failed to give button an image");
			return NULL;
		}
		if (i == 0) {
			but->hovered = 1;
		}
		but->border.x = x;
		but->border.y = y;
		but->border.h = 40;
		but->border.w = 100;
	}
	sj_free(buttons);
}

void menu_draw(menu* men) {
	if (!men) return;
	for (int i = 0; i < men->buttons_count; i++) {
		button_draw(&men->button_list[i]);
	}
	gf2d_sprite_draw(men->border, men->position, NULL, NULL, NULL, NULL, NULL, 0);

}

void menu_close(menu* men) {
	if (!men)return;
	men->active = 0;
}

void menu_open(menu* men) {
	if (!men)return;
	men->active = 1;
}

void menu_think(menu* men) {
	if (!men) return;
	if (gfc_input_command_pressed("navMenuUp")) {
		men->current_button -= 1;
		if (men->current_button < 0) {
			men->current_button += 1;
		}
		else {
			men->button_list[men->current_button].hovered = 1;
			men->button_list[men->current_button - 1].hovered = 0;
		}
	}
	if (gfc_input_command_pressed("navMenuDown")) {
		men->current_button += 1;
		if (men->current_button > men->buttons_count) {
			men->current_button -= 1;
		}
		else {
			men->button_list[men->current_button].hovered = 1;
			men->button_list[men->current_button + 1].hovered = 0;
		}
	}
}

void menu_free(menu *men) {
	if (!men) return;
	if (men->border) {
		gf2d_sprite_free(men->border);
	}
	for (int f = 0; f < men->buttons_count; f++) {
		button_free(&men->button_list[f]);
	}
	memset(men, 0, sizeof(men));


}