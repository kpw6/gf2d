#include "chatbox.h"

#include "simple_logger.h"

#include "fonts.h"

typedef struct {

	chatbox* box_list;

	Uint32* box_count;

}cbmanager;

static cbmanager box_manager = { 0 };


void chatbox_close() {
	int i;
	for (i = 0; i < box_manager.box_count; i++) {
		chatbox_free(&box_manager.box_list[i]);
	}
	free(box_manager.box_list);
	slog("Chatbox system closed");
}

void chatbox_init(Uint32 maxBoxes) {
	box_manager.box_list = gfc_allocate_array(sizeof(chatbox), maxBoxes);
	if (box_manager.box_list == NULL) {
		slog("failed to allocate array in chatbox_list");
		return;
	}
	box_manager.box_count = maxBoxes;
	atexit(chatbox_close);
	slog("Chatbox system initialzed successfully");
}

chatbox* chatbox_new() {
	int i;
	for (i = 0; i < box_manager.box_count; i++) {
		if (!box_manager.box_list[i].inuse) {
			box_manager.box_list[i].inuse = 1;
			return (&box_manager.box_list[i]);
		}
	}
	slog("no space free for new chatbox");
	return NULL;
}

chatbox* chatbox_load(Uint32 textArrayLength, SJson* json) {

	chatbox* box = chatbox_new();

	slog("%s", json->get_string);
	SDL_Color color = { 0, 0, 0 };
	box->maxText = textArrayLength;
	box->font = TTF_OpenFont("PKMN.ttf", 50);
	for (int i = 0; i < textArrayLength; i++) {
		box->text[i] = sj_get_string_value(sj_array_get_nth(json, i));
		slog("text: %s", box->text[i]);
	}
	box->surface = TTF_RenderText_Solid(box->font, box->text[0], color);
	box->texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(), box->surface);
	box->position = vector2d(0, 300);
	box->currentText = 0;

	box->rect.x = 0;
	box->rect.y = 300;
	box->rect.w = 1028;
	box->rect.h = 300;

	return box;
}

void chatbox_draw(chatbox* cbox) {
	fonts_draw(cbox->rect, cbox->texture);
}

void chatbox_free(chatbox* cbox) {
	if (!cbox) {
		slog("No button to free");
		return;
	}
	for (int i = 0; i < cbox->maxText; i++) {
		free(cbox->text[i]);
	}
	SDL_FreeSurface(cbox->surface);
	SDL_DestroyTexture(cbox->texture);
	TTF_CloseFont(cbox->font);
	memset(cbox, 0, sizeof(cbox));
}