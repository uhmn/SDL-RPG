#pragma once
#include "E_FloorItem.h"

class Gun : public FloorItem {
public:
	int bullets;
	int fire_sound;
	int click_sound;
	int equip_sound;

	void initialize();
	void use(vec2d target);
	void itemActivate();
};