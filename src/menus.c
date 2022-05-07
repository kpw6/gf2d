#include "menus.h"

#include <SDL.h>
#include "SDL_ttf.h"

#include "gfc_input.h"
#include "gfc_audio.h"

#include "gf2d_graphics.h"


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

void menu_think(menu* men) {
	if (!men) return;
	if (gfc_input_command_pressed("navMenuUp")) {
		gfc_sound_play(gfc_sound_load("sounds/menuSelect.mp3", 1, 0), 0, 2, -1, -1);
		if ((men->current_button - 1) >= 0) {
			men->current_button -= 1;
			men->button_list[men->current_button + 1].hovered = 0;
			men->button_list[men->current_button].hovered = 1;
		}
	}
	if (gfc_input_command_pressed("navMenuDown")) {
		gfc_sound_play(gfc_sound_load("sounds/menuSelect.mp3", 1, 0), 0, 2, -1, -1);
		if (men->current_button + 1 < men->buttons_count) {
			men->current_button += 1;
			men->button_list[men->current_button - 1].hovered = 0;
			men->button_list[men->current_button].hovered = 1;
		}
	}
	if (gfc_input_command_pressed("Enter")) {
		gfc_sound_play(gfc_sound_load("sounds/menuSelect.mp3", 1, 0), 0, 2, -1, -1);
		button_action(&men->button_list[men->current_button], men);
	}
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
	sj_get_float_value(sj_array_get_nth(position, 1), &y);

	men->position = vector2d(x, y);
	
	border = sj_get_string_value(sj_object_get_value(menu, "border"));
	men->border = gf2d_sprite_load_all(border, 100, 180, 0);
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
	char* bimage = "", *message = "";
	button* but;
	float x, y;

	men->buttons_count = sj_array_get_count(buttons);

	men->button_list = (button*)gfc_allocate_array(sizeof(button), men->buttons_count);

	for (int i = 0; i < men->buttons_count; i++) {
		sbutton = sj_array_get_nth(buttons, i);
		but = menu_button_new(men);

		sj_get_integer_value(sj_object_get_value(sbutton, "type"), &(buttonType)but->type);
		if (but->type < 0) {
			slog("failed to give button a type");
			return NULL;
		}
		message = sj_get_string_value(sj_object_get_value(sbutton, "message"));
		but->message = message;
		if (!but->message) {
			slog("failed to give button a message");
			continue;
		}
		slog("%s", but->message);
		position = sj_object_get_value(sbutton, "position");
		sj_get_float_value(sj_array_get_nth(position, 0), &x);
		sj_get_float_value(sj_array_get_nth(position, 1), &y);
		but->position = vector2d(x, y);
		bimage = sj_get_string_value(sj_object_get_value(sbutton, "image"));
		if (bimage == "" || bimage == NULL) {
			slog("Image not found for button");
		}
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

		but->font = TTF_OpenFont("PKMN.ttf", 20);

		SDL_Color color = { 0, 0, 0 };
		but->surface = TTF_RenderText_Solid(but->font, but->message, color);
		but->texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), but->surface);

	}
	sj_free(buttons);
}

void menu_draw(menu* men) {
	if (!men) return;
	gf2d_sprite_draw(men->border, men->position, NULL, NULL, NULL, NULL, NULL, 0);
	for (int i = 0; i < men->buttons_count; i++) {
		button_draw(&men->button_list[i]);
	}

}

void menu_close(menu* men) {
	if (!men)return;
	men->active = 0;
}

void menu_open(menu* men) {
	if (!men)return;
	men->active = 1;
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

void button_action(button* but, menu *men) {
	switch (but->type) {
		case EXIT:
			men->active = 0;
			break;
		case CLOSE:
			men->active = 0;
	}
}

menu* menu_select(int menuSelect) {
	if (menuSelect <= 0 || menuSelect > menu_manager.menu_count) return NULL;
	return &menu_manager.menu_list[menuSelect];
}