#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "gf2d_sprite.h"

typedef enum {

	EXIT,
	BUY,
	SELL

}buttonType;

typedef struct {
	
	Uint8 hovered; 

	Sprite* image; //the image loaded with the button
	SDL_Rect border; //used for when a button is selected in a menu
	buttonType type; //the type the button is.

	Vector2D position;
	
}button;

button *button_new(buttonType type, Vector2D position, SDL_Rect rect, Sprite* image);

void button_draw(button *but);

void button_action(button* but);

void button_free(button* but);

#endif