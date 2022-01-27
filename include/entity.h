#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf2d_sprite.h"

typedef struct Entity_S {

	Uint8 inuse; //defines if a entity is being used

	Sprite* sprite; //graphic affiliated with entity.

	Vector2D position; //where the entity currently is in the world
	Vector2D acceleration; //time it takes for entity to reach max velocity
	Vector2D velocity; //how fast the entity can move
	Vector2D scale; //how big the entity will be

	float radius; //radius for circular collision

	void (*think)(struct Entity_S* self); //entity think function

	Uint8 health; //health of the entity

}Entity;

/*
* @brief initiates the entity system
* @param maximum amount of entities allowed to be loaded at a time
*/
void entity_system_init(Uint32 maxEntities);

/*
* @brief creates a new entity
*/
Entity* entity_new();

/*
* @brief frees an entity from the system
* @param the entity you want to free
*/
void entity_free(Entity *self);

/*
* @brief draws the sprite connected the entity
* @param the entity you want to draw
*/
void entity_draw(Entity* self);

/*
* @brief draws all entity sprites
*/
void entity_draw_all();

/* 
* @brief think function for entity
* @param entity that is thinking
*/
void entity_think(Entity* self);

/*
* @brief updates all entity think functions
*/
void entity_think_all();

#endif