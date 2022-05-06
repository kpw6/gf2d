#ifndef __SHOP_H__
#define __SHOP_H__

#include "gf2d_sprite.h"
#include "menus.h"

int balance;

typedef enum {

	SEEDS_SQUIRTLE,
	SEEDS_HOPPIP,
	SEEDS_ORAN_BERRY

}shopItem;

typedef struct {

	Uint8 active; /*used for when a menu is open and it pauses the game*/
	shopItem *itemList; /*list of items*/
	shopItem item; /*the item the player will buy from the store*/

	menu* shopMenu; //the menu connected to the shop

	Uint32 price; /*The price of the shop item*/

	Sprite* image; /*The image that loads the shop gui*/


}shop;

/*
* @brief draws the shop menu 
*/
void shop_Draw();

/*
* @brief loads shop date from config
* @param the file that loads the shop
*/
shop shop_Create(char* filename);





#endif