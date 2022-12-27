#include <SDL.h>
#include <vector>
#include <string>
#include "SpriteBase.h"
#include "Vectors.h"
#include "Ents.h"
#include <iostream>
#include "Globals.h"

Sprite* a00() { return new Physical(); }
Sprite* a01() { return new Vessel(); }
Sprite* a02() { return new Tile(); }
Sprite* a03() { return new DeleteBrush(); }
Sprite* a04() { return new Menu(); }
Sprite* a05() { return new MenuB(); }
Sprite* a06() { return new EditorEnt(); }
Sprite* a07() { return new EditorIcon(); }
Sprite* (*entityCreation[])() = { a00, a01, a02, a03, a04, a05, a06, a07 };

SpritePair::SpritePair(Sprite* firstinput, Sprite* secondinput) 
{
	first = firstinput;
	second = secondinput;
}
Sprite* SpritePair::take(bool selection) {
	if		(selection==0) { return first; }
	else if (selection==1) { return second; }
}

Ents::Ents() 
{
	MenuPositions[0] = vec2d(0,0); MenuPositions[1] = vec2d(0, 0);
	HotbarSprites[0] = nullptr; HotbarSprites[1] = nullptr;
	MenuContents[0] = nullptr; MenuContents[1] = nullptr;
	EditorType = "strawberry.png";
	EditorTileOffset = 0;
	EditorEntType = E_Tile;
	EditBrush = nullptr;
	entCount = 0;
	
	AllParticleLayers.push_back(&floorlayer);
	AllParticleLayers.push_back(&walllayer);
	AllParticleLayers.push_back(&midlayer);
	AllParticleLayers.push_back(&playerlayer);
	AllParticleLayers.push_back(&playercosmeticlayer);
	AllParticleLayers.push_back(&editlayer);
}
//void Ents::getEntityTypes() {}
Sprite* Ents::create(unsigned int etype) 
{
	Sprite* ent = (*entityCreation[etype])();
	ent->classtype = etype;
	ent->start();
	Physical* Physicalized = static_cast<Physical*>(ent);
	if (Physicalized != nullptr) { Physicalized->initialize(); }
	allsprites.add(ent);
	return ent;
}
void Ents::update() 
{
	allsprites.update();
}
void Ents::draw(SDL_Renderer* renderer) 
{
	for (spritelist* layer : AllParticleLayers) {
		layer->draw(renderer);
	}
	menulayer1.draw(renderer);
	menulayer2.draw(renderer);
	menulayer3.draw(renderer);
}
int Ents::findCellIndexOfPos(vec2d pos, vec2d vesselPos, unsigned int cellSize) 
{
	int rowLength = (cellSize * 2) + 1;
	vec2d offset = vec2d::Round(vec2d::Div(vec2d::Sub(pos, vesselPos), 32));
	int Xo = offset.x + cellSize;
	int Yo = offset.y + cellSize;
	int Lis = Xo + (Yo * rowLength);
	return Lis;
}
Sprite* Ents::findEntAtCellIndex(int cellIndex, Vessel* vessel, int layer) 
{
	if (std::size(vessel->cellTiles) < cellIndex || std::size(vessel->cellTiles[cellIndex]) < layer) {
		std::cout << "CellIndex Out of bounds error" << std::endl;
		return nullptr;
	}
	else {
		return vessel->cellTiles[cellIndex][layer];
	}
	return nullptr;
}
SpritePair Ents::findBlocksAt(vec2d pos, Vessel* vessel)
{
	if (vessel == nullptr) {
		for (Sprite* v : allvessels.allsprites) {
			SpritePair blocks = findBlocksAt(pos, static_cast<Vessel*>(v));
			if (blocks.first != nullptr || blocks.second != nullptr) {
				return blocks;
			}
		}
		SpritePair emptyblocks(nullptr, nullptr);
		return emptyblocks;
	}
	else {
		int cIndex = findCellIndexOfPos(pos, vessel->position, 25);
		Sprite* ent1 = findEntAtCellIndex(cIndex, vessel, 0);
		Sprite* ent2 = findEntAtCellIndex(cIndex, vessel, 1);
		SpritePair blocks(ent1, ent2);
		return blocks;
	}
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
	entCount += 1;
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

vec2d MousePosToGridPos(double parentX, double parentY)
{
	return vec2d::Mult(vec2d::Round(vec2d::Div(vec2d::Sub(vec2d::Add(vec2d(app.MouseX, app.MouseY), vec2d(globals.CamX, globals.CamY)), vec2d(parentX, parentY)), 32)), 32);
}
vec2d MousePosToVesselPos(double parentX, double parentY)
{
	return vec2d::Round(vec2d::Sub(vec2d::Add(vec2d(app.MouseX, app.MouseY), vec2d(globals.CamX, globals.CamY)), vec2d(parentX, parentY)));
}
vec2d MousePosToPosition(Physical* parent)
{
	if (parent == nullptr) {
		return MousePosToVesselPos(0, 0);
	}
	else {
		return MousePosToVesselPos(parent->position.x, parent->position.y);
	}
}
