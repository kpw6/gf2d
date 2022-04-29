#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "gf2d_sprite.h"

typedef enum {

	EXIT,
	BUY,
	SELL,
	CLOSE

}buttonType;

typedef struct {
	
	Uint8 inuse;
	Uint8 hovered; 

	Sprite* image; //the image loaded with the button
	SDL_Rect border; //used for when a button is selected in a menu
	buttonType type; //the type the button is.
	
	char* message; //the message that runs on the button

	Vector2D position;
	
}button;


/*
* @brief draws the button on the respected position
* @param the button to be drawn
*/
void button_draw(button *but);

/*
* @brief frees a button from memory
* @param the button to be freed
*/
void button_free(button* but);




#endif