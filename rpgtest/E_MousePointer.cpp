#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_MousePointer.h"
#include "Ents.h"
#include "Globals.h"
#include <iostream>

void MousePointer::initialize()
{
	ents.menulayer3.add(this);
	viewmode = V_ALL;
	setSprite("greenpointer.png");
	SDL_Surface* surface = IMG_Load(imagename.c_str());
	SDL_Cursor* mousepointer = SDL_CreateColorCursor(surface, 8, 8);
	SDL_SetCursor(mousepointer);
	SDL_ShowCursor(false);
}

void MousePointer::onTick()
{
	rect.x = app.MouseX;
	rect.y = app.MouseY;
	if (isValid(globals.ActiveMenuItem) && globals.ViewMode == V_1ST) {
		if (globals.ActiveMenuItem->crosshaircolor == 1 && imagename != "yellowtarget.png") {
			setSprite("yellowtarget.png");
		}
		else if (globals.ActiveMenuItem->crosshaircolor == 2 && imagename != "redtarget.png") {
			setSprite("redtarget.png");
		}
	}
	else {
		if (imagename != "greenpointer.png") {
			setSprite("greenpointer.png");
		}
	}
}
