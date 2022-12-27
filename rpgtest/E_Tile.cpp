#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_Tile.h"
#include "Ents.h"
#include "Globals.h"

void Tile::applyParent(Physical* newparent) {
	Physical::applyParent(newparent);
	int i = ents.findCellIndexOfPos(position, parent->position, 25);
	Vessel* vparent = static_cast<Vessel*>(parent);
	vparent->cellTiles[i][stoi(TileSprites[tileoffset][2])] = this;
	vesselCell = i;
	cellLayer = stoi(TileSprites[tileoffset][2]);
}

void Tile::setTileType(unsigned int offset) {
	tileoffset = offset;
	setSprite(TileSprites[offset][0]);
	if (TileSprites[offset][2] == "0") {
		ents.floorlayer.add(this);
	}
	else {
		ents.walllayer.add(this);
	}
}

unsigned int Tile::getTileType() {
	return tileoffset;
}

void Tile::initialize() {
	tileoffset = 0;
}

void DeleteBrush::onTick() {
	Sprite* ent = ents.findBlocksAt(position, static_cast<Vessel*>(parent)).second;
	if (ent != nullptr) { static_cast<Physical*>(ent)->remove(); }
	remove();
} 