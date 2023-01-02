#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_MenuItem.h"
#include "Ents.h"
#include "Globals.h"
#include <iostream>

void MenuItem::onTick()
{
	FloorItem* itemlinkF = static_cast<FloorItem*>(itemlink);
	if (viewmode == globals.ViewMode) {
		bool collision = false;
		if (itemActive == true && app.mousepressed) {
			for (Sprite* v : ents.HotbarSprites) {
				if (vec2d::SquareCollision(v->rect, vec2d(app.MouseX, app.MouseY), 32)) {
					collision = true;
				}
			}
			if (collision == false) {
				use();
			}
		}
		if (ents.MenuHoldingObject == this && app.mouseheld == true) {
			rect.x = app.MouseX;
			rect.y = app.MouseY;
			vec2d v = ents.MenuPositions[inventoryIndex];
			if (vec2d::SquareCollision(v, vec2d(rect), 52) == false) {
				mouseHasLeftButton = true;
			}
			if (held == 0) {
				held = 1;
				if (itemActive == true) {
					mouseHasLeftButton = true;
				}
				setActive(false);
			}
		}
		else {
			if (held == 1) {
				held = 0;
				ents.MenuHoldingObject = nullptr;
				int i2 = 0;
				int i = 0;
				while (std::size(ents.MenuPositions) > i) {
					vec2d v = ents.MenuPositions[i];
					if (vec2d::SquareCollision(v, vec2d(rect), 52)) {
						if (isValid(ents.MenuContents[i])) {
							ents.addInventoryEntity(ents.MenuContents[i], inventoryIndex);
							ents.MenuContents[i]->setInventoryIndex(inventoryIndex);
							if (mouseHasLeftButton == false) {
								setActive(true);
							}
						}
						else {
							ents.addInventoryEntity(nullptr, inventoryIndex);
						}
						ents.addInventoryEntity(this, i);
						inventoryIndex = i;
						i2++;
					}
					i++;
				}
				if (i2 == 0) {
					itemlinkF->exitInventory();
					Physical* CreatureControlLinkParent = static_cast<Physical*>(ents.CreatureControlLink)->parent;
					vec2d destination = MousePosToPosition(CreatureControlLinkParent);
					vec2d realdestination = vec2d(0, 0);
					if (isValid(CreatureControlLinkParent) == false) {
						realdestination = destination;
					}
					else {
						realdestination = vec2d::Add(destination, CreatureControlLinkParent->posOffset);
					}
					vec2d throwspeed = vec2d::Div(vec2d::Sub(destination, itemlinkF->posOffset), globals.gravity);
					double throwmagnitude = vec2d::Distance(throwspeed, vec2d(0,0));
					if (throwmagnitude > 25) {
						throwspeed = vec2d::Div(throwspeed, throwmagnitude / 25);
					}
					Vessel* CreatureControlLinkParentVessel = static_cast<Vessel*>(CreatureControlLinkParent);
					if (vec2d::Largest(vec2d::Sub(destination, itemlinkF->posOffset)) > 48 || isValid(ents.findBlocksAt(realdestination, CreatureControlLinkParentVessel).second)) {
						itemlinkF->pthrow(throwspeed);
					}
					else {
						std::cout << isValid(ents.findBlocksAt(realdestination, CreatureControlLinkParentVessel).second) << std::endl;
						itemlinkF->setPosOffset(destination);
					}
					ents.addInventoryEntity(nullptr, inventoryIndex);
				}
				rect.x = ents.MenuPositions[inventoryIndex].x;
				rect.y = ents.MenuPositions[inventoryIndex].y;
			}
			if (app.mousepressed) {
				if (vec2d::SquareCollision(vec2d(rect), vec2d(app.MouseX, app.MouseY), 52)) {
					ents.setMenuHoldingObject(this);
				}
			}
			mouseHasLeftButton = false;
		}
	}
	if (removing == true) {
		remove();
		return;
	}
}

void MenuItem::initialize()
{
	ents.menulayer1.add(this);
	held = 0;
	inventoryIndex = -1;
	internalIndex = 0;
	viewmode = V_1ST;
	itemlink = nullptr;
	mouseHasLeftButton = false;
	itemActive = false;
	crosshaircolor = 2;
}

void MenuItem::setInventoryIndex(int index)
{
	inventoryIndex = index;
	ents.addInventoryEntity(this, index);
	rect.x = ents.MenuPositions[index].x;
	rect.y = ents.MenuPositions[index].y;
}

void MenuItem::setActive(bool active)
{
	FloorItem* itemlinkF = static_cast<FloorItem*>(itemlink);
	if (active == true) {
		crosshaircolor = itemlinkF->crosshaircolor;
		ents.HotbarSprites[inventoryIndex]->setSprite("smallmenuboxactive.png");
		itemActive = true;
		if (isValid(globals.ActiveMenuItem)) { globals.ActiveMenuItem->setActive(false); }
		globals.ActiveMenuItem = this;
		itemActivate();
	}
	else {
		ents.HotbarSprites[inventoryIndex]->setSprite("smallmenubox.png");
		itemActive = false;
		if (globals.ActiveMenuItem == this) { globals.ActiveMenuItem = nullptr; }
	}
}

void MenuItem::use()
{
	FloorItem* itemlinkF = static_cast<FloorItem*>(itemlink);
	Physical* CreatureControlLinkParent = static_cast<Physical*>(ents.CreatureControlLink)->parent;
	itemlinkF->use(MousePosToPosition(CreatureControlLinkParent));
}

void MenuItem::itemActivate()
{
	FloorItem* itemlinkF = static_cast<FloorItem*>(itemlink);
	itemlinkF->itemActivate();
}
