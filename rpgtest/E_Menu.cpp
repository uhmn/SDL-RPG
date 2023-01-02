#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <iostream>

#include "E_Menu.h"
#include "Globals.h"
#include "Ents.h"


Menu::Menu() : Sprite(0, 0, 32, 32, "strawberry.png") {}

void Menu::start() {
	viewmode = V_EDITOR;
}
void Menu::setPos(vec2d pos) {
	rect.x = pos.x;
	rect.y = pos.y;
}
void Menu::setPosDimensionless(vec2d pos) {
	rect.x = pos.x * WINDOW_WIDTH;
	rect.y = pos.y * WINDOW_HEIGHT;
}
void Menu::setViewMode(int mode) {
	viewmode = mode;
}
void Menu::setSprite(std::string image1) {
	updateSurface(image1);
}
void Menu::update() {
	if (viewmode == globals.ViewMode || viewmode == V_ALL) {
		setAlpha(255);
	}
	else {
		setAlpha(0);
	}
	onTick();
}
void Menu::remove() {
	ents.removeUI(this);
	deconstructSelf();
}
void Menu::onTick() {}

void Menu::initialize() { ents.menulayer1.add(this); }


void MenuB::initialize() { ents.menulayer2.add(this); }
