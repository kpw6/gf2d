#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"


/*
* @brief creates a new player for the game
*/
Entity* player_new();


/*
* @brief think function for the player
* @param the player to think
*/
void player_think(Entity* self);

/*
* @brief think function for the player
* @param the player to think
*/
void player_onTouch(Entity* self);



/*
* @brief think function for the player
* @param the player to think
*/
void player_update(Entity* self);


#endif