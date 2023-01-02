#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_Creature.h"
#include "Ents.h"
#include "Globals.h"
#include <iostream>
#include "Sound.h"

bool Creature::WalkableCheck(vec2d p)
{
	SpritePair ent = ents.findBlocksAt(vec2d::Add(position, p), static_cast<Vessel*>(parent));
	if (isValid(ent.second) == false || isValid(parent) == false) {
		return true;
	}
	else {
		return false;
	}
}

void Creature::initialize()
{
	ents.playerlayer.add(this);
	moveCooldown = 0;
	lastMoveCooldown = 0;
	lastPosition = vec2d(0, 0);
	setSprite("man2.png");
	stepcounter = 0;
	stepcounter2 = 0;
	stepsounds[0] = sound.add("FR1.wav"); stepsounds[1] = sound.add("FR2.wav"); stepsounds[2] = sound.add("FR3.wav");
	stepsounds[3] = sound.add("FL1.wav"); stepsounds[4] = sound.add("FL2.wav"); stepsounds[5] = sound.add("FL3.wav");
	inventory[0] = nullptr; inventory[1] = nullptr;
}

void Creature::onTick()
{
	checkShipCollisions();
	if (moveCooldown > 0) {
		moveCooldown = moveCooldown - 1;
	}
	double Xmove = 0;
	double Ymove = 0;
	if (ents.CreatureControlLink == this && globals.ViewMode == V_1ST) {
		if (moveCooldown < 1) {
			stepcounter++;
			if (app.up) { Ymove--; }
			if (app.down) { Ymove++; }
			if (app.left) { Xmove--; }
			if (app.right) { Xmove++; }
			int movement = abs(Xmove) + abs(Ymove);
			if (movement != 0) {
				lastPosition = position;
				if (movement == 1) {
					moveCooldown = 10;
					lastMoveCooldown = 10;
				}
				else {
					moveCooldown = 14;
					lastMoveCooldown = 14;

					if (WalkableCheck(vec2d(Xmove * 32, Ymove * 32)) == false) {
						if (WalkableCheck(vec2d(Xmove * 32, 0)) == false) {
							Xmove = 0;
						}
						else if (WalkableCheck(vec2d(0, Ymove * 32)) == false) {
							Ymove = 0;
						}
						else {
							Xmove = 0;
							Ymove = 0;
						}
					}
				}
				if (WalkableCheck(vec2d(Xmove * 32, 0)) == true) {
					posOffset = vec2d::Add(posOffset, vec2d(Xmove * 32, 0));
				}
				if (WalkableCheck(vec2d(0, Ymove * 32)) == true) {
					posOffset = vec2d::Add(posOffset, vec2d(0, Ymove * 32));
				}
				if (stepcounter > lastMoveCooldown / 8) {
					if (rand() > (RAND_MAX / 3)) {
						if (rand() > (RAND_MAX / 2)) {
							sound.play(stepsounds[0 + stepcounter2 * 3]);
						}
						else {
							sound.play(stepsounds[1+stepcounter2*3]);
						}
					}
					else {
						sound.play(stepsounds[2+stepcounter2*3]);
					}
					stepcounter = 0;
					stepcounter2 = (stepcounter2 + 1) % 2;
				}
			}
		}
		globals.windowSize = vec2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		position = vec2d(globals.CamX + globals.windowSize.x / 2, globals.CamY + globals.windowSize.y / 2);
		//rect.x = WINDOW_WIDTH / 2;
		//rect.y = WINDOW_HEIGHT / 2;
	}
}

void Creature::remove()
{
	Physical::remove();
	for (Sprite* ent : inventory) {
		FloorItem* fent = static_cast<FloorItem*>(ent);
		fent->exitInventory();
	}
}
