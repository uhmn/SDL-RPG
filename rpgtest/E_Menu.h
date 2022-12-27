#pragma once
#include "MathFunctionsHeader.h"
#include "SpriteBase.h"
#include "Vectors.h"
#include <vector>
#include <string>

class Menu : public Sprite {
public:
	int viewmode;

	Menu();
	virtual void start();
	virtual void setPos(vec2d pos);
	virtual void setPosDimensionless(vec2d pos);
	virtual void setViewMode(int mode);
	virtual void setSprite(std::string image1);
	virtual void update();
	virtual void remove();
	virtual void onTick();
	virtual void initialize();
};

class MenuB : public Menu {
public:
	void initialize();
};