#ifndef __CHATBOX_H__
#define __CHATBOX_H__

#include "SDL_ttf.h"

#include "simple_json.h"

#include "gf2d_sprite.h"
#include "gfc_text.h"

typedef struct {
	Uint32 currentText;
	Uint32 maxText;
	
	Uint8 inuse;

	SDL_Rect rect;

	TTF_Font* font; //the font that is used for the border
	SDL_Surface* surface;
	SDL_Texture* texture;

	char* text[2014];

	Vector2D position; 

}chatbox;
void chatbox_close();

void chatbox_init(Uint32 maxBoxes);

chatbox* chatbox_new();

chatbox* chatbox_load(Uint32 textArrayLength, SJson* json);

void chatbox_draw(chatbox* cbox);

void chatbox_free(chatbox* cbox);

#endif