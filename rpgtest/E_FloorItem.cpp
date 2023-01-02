#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_FloorItem.h"
#include "Ents.h"
#include "Globals.h"
#include <iostream>
#include "Sound.h"

void FloorItem::initialize()
{
	ents.midlayer.add(this);
	inside = nullptr;
	uiItem = nullptr;
	invIndex = 0;
	onFloor = true;
	velocity = vec2d(0,0);
	height = 0.5;
	angle = 0;
	crosshaircolor = 1;
	spinSpeed = 0;
	hitsound = sound.add("tink.wav");
}

void FloorItem::pressed()
{
	int space = -1;
	int i = 0;
	while (i < std::size(ents.MenuContents)) {
		if (isValid(ents.MenuContents[i]) == false) { space = i; }
		i++;
	}
	if (space != -1) {
		Creature* CreatureControlLinkCreature = static_cast<Creature*>(ents.CreatureControlLink);
		if (vec2d::Largest(vec2d::Sub(CreatureControlLinkCreature->position, position)) < 48) {
			putInside(CreatureControlLinkCreature, space);
		}
	}
}

void FloorItem::onTick()
{
	if (globals.ViewMode == V_1ST) {
		if (vec2d::SquareCollision(vec2d(rect), vec2d(app.MouseX, app.MouseY), 16)) {
			if (app.mousepressed) {
				pressed();
			}
		}
	}
	if (onFloor == false) {
		spin();
		SpritePair tiles = ents.findBlocksAt(vec2d::Add(position, velocity), static_cast<Vessel*>(parent));
		if (isValid(tiles.second)) {
			onWallHit(velocity);
			vec2d position1 = vec2d::Mult(vec2d::Round(vec2d::Div(posOffset, 32)), 32);
			vec2d position2 = static_cast<Tile*>(tiles.second)->posOffset;
			vec2d direction = vec2d::Round(vec2d::Div(vec2d::Sub(position1, position2), 32));
			double hitspeed = vec2d::Distance(velocity, vec2d(0, 0));
			if (hitspeed > 3) {
				sound.play(hitsound, hitspeed);
			}
			if (abs(direction.x) + abs(direction.y) > 1) {
				if (hitspeed > 30) {
					remove();
				}
				velocity = vec2d::Mult(velocity, -0.05);
			}
			else if (direction.x != 0) {
				velocity = vec2d(velocity.x * (-0.35), velocity.y);
			}
			else if (direction.y != 0) {
				velocity = vec2d(velocity.x, velocity.y * (-0.35));
			}
		}
		posOffset = vec2d::Add(posOffset, velocity);
		if (isValid(tiles.first) == false && isValid(tiles.second) == false && isValid(parent) == true) {
			unParent();
		}
		height = height - globals.gravity / 200;
		if (height < 0) {
			setOnFloor(true);
		}
	}
	else {
		checkShipCollisions();
		if (isValid(parent) == false) {
			remove();
		}
	}
}

void FloorItem::putInside(Physical* ent, int index)
{
	inside = ent;
	setPos(ent->calculatePosition());
	setParent(ent);
	posOffset = vec2d(0, 0);
	velocity = vec2d(0, 0);
	setOnFloor(true);
	angle = 0;
	if (ents.CreatureControlLink == ent) {
		uiItem = static_cast<Menu*>(ents.create(E_MenuItem));
		MenuItem* uiItemI = static_cast<MenuItem*>(uiItem);
		uiItemI->setSprite(imagename);
		uiItemI->setInventoryIndex(index);
		uiItemI->itemlink = this;
		invIndex = index;
	}
	setAlpha(0);
}

bool FloorItem::isInside()
{
	if (isValid(inside))	{ return true; }
	else					{ return false; }
}

void FloorItem::exitInventory()
{
	setParent(inside->parent);
	setPosOffset(inside->posOffset);
	inside = nullptr;
	uiItem->removing = true;
	uiItem = nullptr;
	setAlpha(255);
	spinSpeed = 0;
	angle = 0;
}

std::string FloorItem::getData()
{
	std::string ans = Physical::getData();
	int newinside = 0;
	if (isValid(inside)) {
		newinside = inside->id;
	}
	ans = ans + data_number_node(std::to_string(newinside));
	ans = ans + data_number_node(std::to_string(invIndex));
	return ans;
}

void FloorItem::enterData(std::vector<std::string> data)
{
	Physical::enterData(data);
	inside = static_cast<Physical*>(ents.SIDToEnt(stoi(data[7])));
	if (isValid(inside) == false) {
		inside = nullptr;
	}
	else {
		putInside(inside, stoi(data[8]));
	}

}

void FloorItem::setOnFloor(bool set)
{
	onFloor = set;
	if (set == true) {
		velocity = vec2d(0, 0);
		height = 0;
		posOffset = vec2d::Round(posOffset);
	}
}

double FloorItem::getAbsVelocity()
{
	return vec2d::Distance(velocity, vec2d(0,0));
}

void FloorItem::pthrow(vec2d vel)
{
	height = 0.5;
	velocity = vel;
	setOnFloor(false);
	spinSpeed = (float(rand()) / float(RAND_MAX)) * 32 - 16;
}

void FloorItem::setSprite(std::string image1)
{
	Physical::setSprite(image1);
}

void FloorItem::spin()
{
	vec2d center = vec2d(rect);
	angle = angle + spinSpeed;
	angle = angle % 360;
}

void FloorItem::use(vec2d target)
{
}

void FloorItem::onWallHit(vec2d velocity)
{
}

void FloorItem::itemActivate()
{
}
