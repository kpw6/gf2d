#include "AI.h"

#include "physics.h"

int i = 0, c = 0;


void monster_movement_AI(Entity* monster) {
	if (i < 10) {
	monster_movement(monster, monster->lastMovement);
	i++;
	}
	else {
		i = 0;
		monster->lastMovement = gfc_random() * 5;
	}
	

}