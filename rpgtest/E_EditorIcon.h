#pragma once
#include "E_Menu.h"

class EditorIcon : public Menu {
	int tileoffset;
	int enttype;

	void initialize();
	void setSprite(std::string image1);
	void setproperties(int offset);
	void onTick();
};