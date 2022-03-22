#ifndef __MENUS_H__
#define __MENUS_H__

#include "button.h"

typedef struct {

	Uint8 inuse;
	Uint8 active;

	Uint32 buttons_amount;
	Uint32 buttons_count;

	button* button_list; //the list to give for buttons


}menu;

void menu_manager_close();

void menu_manager_init(Uint32 maxMenus);

menu* menu_new();

void menu_draw();

void menu_close();

void menu_open();





#endif