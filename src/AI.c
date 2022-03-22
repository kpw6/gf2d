#include "AI.h"

#include "physics.h"

int i = 0, c = 0;


void monster_movement_AI(Entity* monster) {
	if (i < 10) {
	monster_movement(monster, c);
	i++;
	}
	else {
		i = 0;
		c = gfc_random() * 5;
	}
	

}