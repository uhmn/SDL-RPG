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
		//make self partially visible
		posOffset = MousePosToGridPos(parent->position.x, parent->position.y);
		//position = posOffset;
		if (app.mousepressed == true) {
			int entlayer = stoi(TileSprites[ents.EditorTileOffset][2]);
			SpritePair previous = ents.findBlocksAt(position, static_cast<Vessel*>(parent));
			if (previous.take(entlayer) != nullptr) {
				static_cast<Physical*>(previous.take(entlayer))->remove();
			}
			if (entlayer == 0) {
				if (previous.second != nullptr) {
					static_cast<Physical*>(previous.second)->remove();
				}
			}
			Tile* placed = static_cast<Tile*>(ents.create(ents.EditorEntType));
			placed->setTileType(ents.EditorTileOffset);
			placed->setSprite(ents.EditorType);
			placed->setPos(position);
			placed->setParent(parent);
		}
	}
	else {
		//make image invisible
	}
}