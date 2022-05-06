#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"


/*
* @brief creates a new enemy for the game
*/
Entity* enemy_new();


/*
* @brief think function for the enemy
* @param the player to think
*/
void enemy_think(Entity* self);

/*
* @brief think function for the enemy
* @param the player to think
*/
void enemy_update(Entity* self);

/*
* @brief ontouch function for the enmy
* @param the player to think
*/
void enemy_onTouch(Entity* self);

void enemy_openMenu(Entity* self);


#endif