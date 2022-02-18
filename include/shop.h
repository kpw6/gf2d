#ifndef __SHOP_H__
#define __SHOP_H__

#include "gf2d_sprite.h"


typedef enum {

	SEEDS_SQUIRTLE,
	SEEDS_HOPPIP,
	SEEDS_ORAN_BERRY

}shopItem;

typedef struct {

	shopItem item; /*the item the player will buy from the store*/

	Uint32 price; /*The price of the shop item*/

	Sprite* image; /*The image that loads the shop gui*/

}shop;
#endif