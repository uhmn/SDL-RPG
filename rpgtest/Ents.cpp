#include <SDL.h>
#include <vector>
#include <string>
#include "SpriteBase.h"
#include "Vectors.h"
#include "Physical.h"
#include "Ents.h"

Sprite* createPhysical() {
	Sprite* newsprite = new Physical();
	return newsprite;
}
Sprite* (*functptr[])() = { createPhysical };

Ents::Ents() 
{
	MenuPositions[0] = vec2d(0,0); MenuPositions[1] = vec2d(0, 0);
	HotbarSprites[0] = nullptr; HotbarSprites[1] = nullptr;
	MenuContents[0] = nullptr; MenuContents[1] = nullptr;
	EditorType = "strawberry.png";
	EditorTileOffset = 0;
	EditorEntType = "Tile";
	EditBrush = nullptr;
	entCount = 0;
	
}
//void Ents::getEntityTypes() {}
Sprite* Ents::create(unsigned int etype) 
{
	Sprite* ent = (*functptr[etype])();
	ent->classtype = etype;
	ent->start();
	Physical* Physicalized = static_cast<Physical*>(ent);
	if (Physicalized != nullptr) { Physicalized->initialize(); }
	allsprites.add(ent);
	return ent;
}
void Ents::update() 
{

}
void Ents::draw(SDL_Renderer* renderer) 
{

}
int Ents::findCellIndexOfPos(vec2d pos, vec2d vesselPos, unsigned int cellSize) 
{
	return 69420;
}
Sprite* Ents::findEntAtCellIndex(int cellIndex, Sprite* vessel, int layer) 
{
	Sprite* thing = new Physical(); //temp
	return thing;
}
Sprite* Ents::findBlocksAt(vec2d pos, Sprite* vessel) 
{
	Sprite* thing = new Physical(); //temp
	return thing;
}
void Ents::setMenuHoldingObject(Sprite* ent) 
{

}
void Ents::addInventoryEntity(Sprite* ent, int index) 
{

}
void Ents::findMouseover() 
{

}
Sprite* Ents::SIDToEnt(int SID) 
{
	Sprite* thing = new Physical(); //temp
	return thing;
}
void Ents::incrementEntCounter() 
{

}
//SaveData* Ents::getAllTable() {}
void Ents::deleteAll() 
{

}
void Ents::remove(Sprite* ent) 
{

}
void Ents::removeUI(Sprite* ent) 
{

}

Ents ents;