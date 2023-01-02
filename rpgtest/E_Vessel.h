#pragma once
#include "SpriteBase.h"
#include "Vectors.h"
#include "E_Physical.h"

class Vessel : public Physical {
public:
	std::vector<std::vector<Physical*>> cellTiles;
	vec2d velocity;

	Vessel();
	void initialize();
	void onTick();
	void enterData(); //do nothing or else it will break
};