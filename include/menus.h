#ifndef __MENUS_H__
#define __MENUS_H__

#include "button.h"

#include "simple_json.h"

typedef struct {

	Uint8 inuse; //if the menu memory space is taken.
	Uint8 active; //if the menu is the one that should be activated

	Uint32 buttons_count; //amount of buttons in button list;
	Uint32 current_button; //Selected button

	button* button_list; //the list to give for buttons

	Sprite* border; //menu border image

	Vector2D position; //position to show the menu


}menu;

/*
* @brief closes the menu manager
*/
void menu_manager_close();

/*
* @brief initialized the menu manager
* @param the max amount of menus that can be loaded in memory
*/
void menu_manager_init(Uint32 maxMenus);

/*
* @brief loads a menu from json
* @param the location of the filename in files
* @param the menu to load from json in json
*/
menu* menu_load(char *filename, char* menuChoice);

/*
* @brief creates a new menu
*/
menu* menu_new();

/*
* @brief creates a button for the menu
* @param the menu that the button is assigned too
*/
button* menu_button_new(menu *men);


void menu_button_load(menu* men, SJson *buttons);

/*
* @brief draws the menu in entirity
* @param the menu to draw
*/
void menu_draw(menu *men);

/*
* @brief stops the drawing and update of a menu
* @param the menu to close
*/
void menu_close(menu *men);

/*
* @brief starts the drawing and update of a menu
* @param the menu to start drawing
*/
void menu_open(menu *men);

/*
* @brief the think function for the menu
* @param the menu that is thinking
*/
void menu_think(menu* men);

/*
* @brief the free function
* @param the menu that is being freed
*/
void menu_free(menu* men);



#endif