#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "Ents.h"
#include "Globals.h"
#include "E_Gun.h"
#include <iostream>
#include "Sound.h"

void Gun::initialize()
{
	FloorItem::initialize();
	crosshaircolor = 2;
	setSprite("gun.png");
	fire_sound = sound.add("pistol_fire.wav");
	click_sound = sound.add("click.wav");
	equip_sound = sound.add("gun_equip.wav");
	bullets = 7;
}

void Gun::use(vec2d target)
{
	if (bullets > 0) {
		FloorItem* bullet = static_cast<FloorItem*>(ents.create(E_FloorItem));
		bullet->setSprite("shell.png"); this;
		bullet->setParent(getVessel());
		vec2d localposOffset = vec2d(0, 0);
		if (isInside()) {
			bullet->setPosOffset(parent->posOffset);
			localposOffset = parent->posOffset;
		}
		else {
			bullet->setPosOffset(posOffset);
			localposOffset = posOffset;
		}
		vec2d offset = vec2d::Sub(target, localposOffset);
		double magnitude = vec2d::Distance(offset, vec2d(0, 0));
		offset = vec2d::Div(offset, (magnitude / 40));
		bullet->pthrow(offset);
		bullet->height = 1;
		sound.play(fire_sound);
		bullets -= 1;
	}
	else {
		sound.play(click_sound);
	}
}

void Gun::itemActivate()
{
	sound.play(equip_sound);
}
