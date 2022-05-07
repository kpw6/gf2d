#include "fonts.h"

#include "simple_logger.h"

#include "SDL_ttf.h"

void fonts_init() {
	if (TTF_Init() == -1) {
		slog("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	slog("fonts initialized");
}

void fonts_close(TTF_Font* font) {
	TTF_CloseFont(font);
}

void fonts_draw(char* text, SDL_Rect position, SDL_Texture* texture) {
	SDL_RenderCopy(gf2d_graphics_get_renderer(), texture, NULL, &position);
}