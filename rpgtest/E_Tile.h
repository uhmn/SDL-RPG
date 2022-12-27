#pragma once
#include "SpriteBase.h"
#include "Vectors.h"
#include "E_Physical.h"

class Tile : public Physical {
public:
	unsigned int tileoffset;

	void applyParent(Physical* newparent);
	void setTileType(unsigned int offset);
	unsigned int getTileType();
	void initialize();
};

class DeleteBrush : public Tile {
public:
	void onTick();
};