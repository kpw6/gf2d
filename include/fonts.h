#ifndef __FONTS_H__
#define __FONTS_H__
#include <SDL.h>
#include "SDL_ttf.h"

#include "gf2d_graphics.h"
#include "gfc_vector.h"


/*
* @brief intitalizes the fonts thing
*/
void fonts_init();

void fonts_close(TTF_Font* font);

void fonts_draw(SDL_Rect position, SDL_Texture* texture);

#endif
