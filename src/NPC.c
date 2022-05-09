#include "NPC.h"

#include "physics.h"
#include "menus.h"

#include "gfc_input.h"

#include "simple_logger.h"

void NPC_think() {

}

void NPC_onTouch(Entity* self, Entity* other) {
	pushback_entity(self, other);
}

void NPC_openMenu(Entity* self) {
	if (!self) return;
	if (gfc_input_command_pressed("Menu1") && !menu_select(2)->active) {
		slog("robot");
		menu_select(2)->active = 1;
	}
	if (menu_select(2)->active) {
		menu_draw(menu_select(2));
		menu_think(menu_select(2));
	}
}

Entity* NPC_new() {

	Entity* enemy = entity_new();
	if (!enemy) {
		slog("failed to make new NPC entity");
		return NULL;
	}
	enemy->sprite = gf2d_sprite_load_all("images/N.png", 64, 64, 4);
	if (!enemy->sprite) {
		slog("Failed to assign sprite to player");
	}
	enemy->position = vector2d(300, 300);
	vector2d_add(enemy->min, enemy->position, vector2d(-10, -10));
	vector2d_add(enemy->max, enemy->position, vector2d(10, 10));
	vector2d_add(enemy->cmin, enemy->position, vector2d(-20, -20));
	vector2d_add(enemy->cmax, enemy->position, vector2d(20, 20));
	//enemy->radius = 1;
	enemy->frame = 0;
	enemy->think = NPC_think;
	enemy->onTouch = NPC_onTouch;
	enemy->menuOpen = NPC_openMenu;


	return enemy;
}
