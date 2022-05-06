#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "entity.h"

#include "borders.h"

/*
* @brief a basic movement or bounce effect for an entity
* @param The entity that you want to move
* @param speed of the movement on the x axis
* @param speed of the movement on the y axis
*/
void simple_movement(Entity* self, float speedx, float speedy);

/*
* @brief teleports an entity to a new position
* @param The entity that will teleport
* @param position of where to place the entity
*/
void entity_teleport(Entity* self, Vector2D position);

/*
* @brief makes sure entities don't faze through eachother
*/
void pushback_entity(Entity* self, Entity* other);

/*
* @brief makes sure entities don't faze through borders
*/
void pushback_entity_on_border(Entity* self, border* bord);


void player_movement(Entity* self);


/*
* @brief basic movement funtion for monsters when in control
* @param The entity that is being moved
*/
void monster_movement_playable(Entity* self);

void monster_movement(Entity* self);

/* 
* @brief simple collision detection between two entities using min and max
* @param The entity that inflicted the collision
* @param the entity that has been collided with
* @return true if collided, false if not
*/
Uint8 ent_rect_collision(Entity* self, Entity* other);

/*
* @brief simple collision detection between two entities using min and max
* @param The entity that inflicted the collision
* @param the entity that has been collided with
* @return true if collided, false if not
*/
Uint8 ent_crect_collision(Entity* self, Entity* other);

/*
* @brief simple collision detection between two entities using radius
* @param The entity that inflicted the collision
* @param the entity that has been collided with
* @return true if collided, false if not
*/
Uint8 ent_circ_collision(Entity* self, Entity* other);

/*
* @brief simple collision detection between an entity and a border
* @param The entity that inflicted the collision
* @param the border that is being touched
* @return true if collided, false if not
*/
Uint8 ent_border_collision(Entity* self, border* other);



#endif