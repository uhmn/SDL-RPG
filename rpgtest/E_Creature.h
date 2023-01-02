#pragma once
#include "SpriteBase.h"
#include "Vectors.h"
#include "E_Physical.h"

class Creature : public Physical {
public:
	int moveCooldown;
	int lastMoveCooldown;
	vec2d lastPosition;
	int stepcounter;
	int stepcounter2;
	Sprite* inventory[2];
	int stepsounds[6];

	bool WalkableCheck(vec2d p);
	void initialize();
	void onTick();
	void remove();
};