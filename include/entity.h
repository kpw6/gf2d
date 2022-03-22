#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf2d_sprite.h"

typedef enum {

	CROP_SQUIRTLE,
	CROP_HOPPIP,
	CROP_ORAN_BERRY

}cropType;

typedef enum {

	MONSTER_SQUIRTLE,
	MONSTER_HOPPIP

}monsterType;

typedef struct Entity_S {

	Uint8 inuse; //defines if a entity is being used
	Uint8 solid; //if true this entity should clip the world
	Uint8 active; //checks if entity is in memory just not on screen
	Uint8 control; //check if entity is in control.
	Uint8 isPlayer; //a tag for the player to wear.

	Sprite* sprite; //graphic affiliated with entity.

	float frame; //the frame the sprite is on
	float radius; //radius for circular collision detection
	float lifeSpan; //used for entities that should only spawn for a certain amount of time.

	Vector2D position; //where the entity currently is in the world
	Vector2D acceleration; //time it takes for entity to reach max velocity
	Vector2D velocity; //how fast the entity can move
	Vector2D scale; //how big the entity will be
	Vector2D min, max; //min and max are used for rectangular collision detection


	void (*think)(struct Entity_S* self); //entity think function
	void (*update)(struct Entity_S* self); //entity update function
	void (*onTouch)(struct Entity_S* self, struct Entity_S* other); //entity ontouch function

	int health; //health of the entity
	int damage; //amount of damage the entity can enflict
	int direction; //decides what direction the entity should travel

	char *attackType;

	cropType type; /*type of crop to create*/


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

/*
* @brief update function for entity
* @param entity that is updating
*/
void entity_update(Entity* self);

/*
* @brief updates all entity update functions
*/
void entity_update_all();

/*
* @brief onTouch function for entity
* @param entity that is doing the collision
* @param entity that is being collided
*/
void entity_onTouch(Entity* self, Entity* other);

/*
* @brief test all entities for collision
*/
void entity_collision_tests();

/*
* @brief will retrieve the player entity
*/
Entity *entity_isPlayer();

/*
* @brief this will layer the entities properly
* 
*/
void entity_layer_sort();

#endif