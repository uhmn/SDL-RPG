#pragma once
#include "SpriteBase.h"
#include "Vectors.h"
#include "E_Physical.h"
#include "E_MenuItem.h"
#include "E_Menu.h"

class FloorItem : public Physical {
public:
	Physical* inside;
	Menu* uiItem;
	int invIndex;
	bool onFloor;
	vec2d velocity;
	float height;
	int crosshaircolor;
	double spinSpeed;
	int hitsound;

	virtual void initialize();
	void pressed();
	void onTick();
	void putInside(Physical* ent, int index);
	bool isInside();
	void exitInventory();
	std::string getData();
	void enterData(std::vector<std::string> data);
	void setOnFloor(bool set);
	double getAbsVelocity();
	void pthrow(vec2d vel);
	void setSprite(std::string image1);
	void spin();
	virtual void use(vec2d target);
	virtual void onWallHit(vec2d velocity);
	virtual void itemActivate();
};