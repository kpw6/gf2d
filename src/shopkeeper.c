#include "shopkeeper.h"

#include "physics.h"
#include "menus.h"

#include "gfc_input.h"

#include "simple_logger.h"

void Shopkeeper_think() {

}

void Shopkeeper_onTouch(Entity* self, Entity* other) {
	pushback_entity(self, other);
}

void Shopkeeper_openMenu(Entity* self) {
	if (!self) return;
	if (gfc_input_command_pressed("Menu1") && !menu_select(1)->active) {
		slog("robot");
		menu_select(1)->active = 1;
	}
	if (menu_select(1)->active) {
		menu_draw(menu_select(1));
		menu_think(menu_select(1));
	}
}

Entity* Shopkeeper_new() {

	Entity* enemy = entity_new();
	if (!enemy) {
		slog("failed to make new NPC entity");
		return NULL;
	}
	enemy->sprite = gf2d_sprite_load_all("images/SK.png", 64, 64, 4);
	if (!enemy->sprite) {
		slog("Failed to assign sprite to player");
	}
	enemy->position = vector2d(700, 300);
	vector2d_add(enemy->min, enemy->position, vector2d(-10, -10));
	vector2d_add(enemy->max, enemy->position, vector2d(10, 10));
	vector2d_add(enemy->cmin, enemy->position, vector2d(-20, -20));
	vector2d_add(enemy->cmax, enemy->position, vector2d(20, 20));
	enemy->frame = 0;
	enemy->think = Shopkeeper_think;
	enemy->onTouch = Shopkeeper_onTouch;
	enemy->menuOpen = Shopkeeper_openMenu;


	return enemy;
}
