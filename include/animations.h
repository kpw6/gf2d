#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "entity.h"


/*
* @brief the animation function for the player entity when it's in motion.
* @param the entity the player is set too animation
* @param the int that represents what button was last pressed
*/
void player_animate_movement(Entity* self, int lastKey);

/*
* @brief returns the player animation to idle state.
* @param the entity the player is set too animation
* @param the int that represents what button was last pressed
*/
void player_animate_return_idle(Entity* self, int lastKey);
#endif