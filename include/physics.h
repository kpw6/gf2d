#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "entity.h"

/*
* @brief a basic movement or bounce effect for an entity
* @param The entity that you want to move
* @param speed of the movement on the x axis
* @param speed of the movement on the y axis
*/
void simple_movement(Entity* self, float speedx, float speedy);

/* 
* @brief simple collision detection between two entities using min and max
* @param The entity that inflicted the collision
* @param the entity that has been collided with
* @return true if collided, false if not
*/
Uint8 ent_rect_collision(Entity* self, Entity* other);


#endif