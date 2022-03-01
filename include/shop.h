#ifndef __SHOP_H__
#define __SHOP_H__

#include "gf2d_sprite.h"


typedef enum {

	SEEDS_SQUIRTLE,
	SEEDS_HOPPIP,
	SEEDS_ORAN_BERRY

}shopItem;

typedef struct {

	Uint8 active; /*used for when a menu is open and it pauses the game*/
	shopItem *itemList; /*list of items*/
	shopItem item; /*the item the player will buy from the store*/

	Uint32 price; /*The price of the shop item*/

	Sprite* image; /*The image that loads the shop gui*/

	Vector2D position; /*The position of the shop menu*/
	Vector2D scale; /*the size of the menu*/


}shop;

/*
* @brief draws the shop menu 
*/
void shop_Draw();


shop shop_Create(char* filename);





#endif