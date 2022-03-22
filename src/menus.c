#include "menus.h"
#include "simple_logger.h"


typedef struct {

	menu* menu_list;
	Uint32 menu_count;

}menuManager;

static menuManager menu_manager = { 0 };

void menu_manager_close() {
	int i;
	for (i = 0; i < menu_manager.menu_count; i++) {
		entity_free(&menu_manager.menu_list[i]);
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

menu* menu_new();

void menu_draw(menu* men) {
	
}

void menu_close(menu* men) {
	if (!men)return;
	men->active = 0;
}

void menu_open(menu* men) {
	if (!men)return;
	men->active = 1;
}