#include "menu.h"
#include "font.h"
#include "utils.h"

#include <vita2d.h>
#include <cmath>

#include <cstdio>

Menu::Menu(Menu * prevMenu, int x, int y, int background_colour)
	: x(x), y(y), background_colour(background_colour), current_menu_selection(0)
{
	this->name = new std::string("");

	this->prevMenu = prevMenu;

	for(int i = 0; i < 10; i++)
	{
		this->menuItems[i] = NULL;
	}
}

Menu::Menu(Menu * prevMenu, int x, int y, int background_colour, char * name) 
	: x(x), y(y), background_colour(background_colour), current_menu_selection(0)
{
	this->name = new std::string(name);

	this->prevMenu = prevMenu;

	for(int i = 0; i < 10; i++)
	{
		this->menuItems[i] = NULL;
	}
}

Menu::~Menu() {
	delete this->name;

	for(int i = 0; i < this->total_menu_items; i++)
	{
		delete this->menuItems[i];
	}
}

//draws the menu and the items
void Menu::draw() {
	vita2d_set_clear_color(this->background_colour);

	font_draw_string(this->x, this->y, this->background_colour, this->name->c_str());

	for(int i = 0; i < this->total_menu_items; i++)
	{
		this->menuItems[i]->draw();
	}
}

//adds a menu to the menu
void Menu::addMenuItem(MenuItem * item) {

	//we can only have 10 menu items for now
	if(this->total_menu_items >= 9)
	{
		return;
	}

	this->menuItems[total_menu_items] = item;
}

//
void Menu::handleTouch(int x , int y)
{
	//TODO: Find the correct menu item
	int ceil_y = ceil(y / 16); //font height = 16

	if (ceil_y >= this->total_menu_items)
	{
		return;
	}

	this->menuItems[ceil_y]->handleSelection();
}

// handles the dpad movement
// int up_down is either 1 or -1
// 1 is up, -1 is down
void Menu::handleDpad(int up_down, bool selected)
{
	if(selected)
	{
		this->menuItems[this->current_menu_selection]->handleSelection();
		return;
	}
	if(up_down != 1 && up_down != -1)
	{
		return;
	}

	this->current_menu_selection += up_down;

	//boundary checks
	if(this->current_menu_selection == 0 && up_down == -1)
	{
		this->current_menu_selection = 0;
	}
	else if(this->current_menu_selection == total_menu_items && up_down == 1)
	{
		this->current_menu_selection = (total_menu_items - 1);
	}
}