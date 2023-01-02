#pragma once
#include "E_Menu.h"
#include "E_FloorItem.h"

class MenuItem : public Menu {
public:
	int held;
	bool itemActive;
	int inventoryIndex;
	int internalIndex;
	bool mouseHasLeftButton;
	Physical* itemlink;
	int crosshaircolor;

	void onTick();
	void initialize();
	void setInventoryIndex(int index);
	void setActive(bool active);
	void use();
	void itemActivate();
};