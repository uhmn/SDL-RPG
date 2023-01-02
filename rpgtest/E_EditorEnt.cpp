#include "E_EditorEnt.h"
#include "Globals.h"
#include "Ents.h"
#include <iostream>

void EditorEnt::initialize() {
	ents.editlayer.add(this);
	ents.EditBrush = this;
}
void EditorEnt::onTick() {
	if (globals.ViewMode == V_EDITOR && globals.Mouseover == M_GAME) {
		setAlpha(128);
		posOffset = MousePosToGridPos(parent->position.x, parent->position.y);
		if (app.mousepressed == true) {
			int entlayer = stoi(TileSprites[ents.EditorTileOffset][2]);
			SpritePair previous = ents.findBlocksAt(position, static_cast<Vessel*>(parent));
			if (isValid(previous.take(entlayer))) {
				static_cast<Physical*>(previous.take(entlayer))->remove();
			}
			if (entlayer == 0) {
				if (isValid(previous.second)) {
					static_cast<Physical*>(previous.second)->remove();
				}
			}
			Sprite* splaced = ents.create(ents.EditorEntType);
			Tile* placed = static_cast<Tile*>(splaced);
			placed->setTileType(ents.EditorTileOffset);
			placed->setSprite(ents.EditorType);
			placed->setPos(position);
			placed->setParent(parent);
		}
	}
	else {
		setAlpha(0);
	}
}