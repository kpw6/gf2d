#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "entity.h"

/* 
* @brief simple collision detection between two entities using min and max
* @param The entity that inflicted the collision
* @param the entity that has been collided with
* @return true if collided, false if not
*/
Uint8 ent_rect_collision(Entity* self, Entity* other);


#endif