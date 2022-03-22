#ifndef __ATTACKS_H__
#define __ATTACKS_H__

#include "Entity.h"


/*
* @brief creates a new attack for use
* @param filename to load the attack from
* @param the type of attack to load
* @param the position of where to spawn the attack,
*/
Entity* attack_new(char* filename, char *type, Vector2D positon);

/*
* @brief think function for the attack
* @param the entity that is thinking
*/
void attack_think(Entity* self);

/*
* @brief touch fucntion for an attack.
* @param the attack.
* @param the entity being touched.
*/
void attack_onTouch(Entity* self, Entity* other);

/*
* @brief decides what direction to send the attack
*/
void attack_direction(Entity* self);

#endif