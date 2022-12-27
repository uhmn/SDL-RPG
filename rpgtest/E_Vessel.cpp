#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_Vessel.h"
#include "Ents.h"

Vessel::Vessel() : Physical() {}

void Vessel::initialize() {
	ents.floorlayer.add(this);
	ents.allvessels.add(this);
	std::vector<Physical*> blankthing;
	blankthing.resize(2, nullptr);
	int i = 0;
	while (2601 > i) {
		cellTiles.resize(2600, blankthing);
		i += 1;
	}
	velocity = vec2d(-0.1, -0.1);
}

void Vessel::onTick() {
	posOffset = vec2d::Add(posOffset, velocity);
}

//void Vessel::enterData() {} //do nothing or else it will break