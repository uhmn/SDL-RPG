#include <SDL.h>
#include <vector>
#include <string>
#include "SpriteBase.h"
#include "Vectors.h"
#include "Ents.h"
#include <iostream>
#include "Globals.h"
#include <map>

std::map<std::string, int> StringIntEtype = {
	{ "Particle"		, 0		}, 
	{ "Vessel"			, 1		},
	{ "Tile"			, 2		},
	{ "DeleteBrush"		, 3		},
	{ "Menu"			, 4		},
	{ "MenuB"			, 5		},
	{ "EditorEnt"		, 6		},
	{ "EditorIcon"		, 7		},
	{ "SaveLoadButton"	, 8		},
	{ "SaveButton"		, 9		},
	{ "LoadButton"		, 10	},
	{ "Creature"		, 11	},
	{ "MenuItem"		, 12	},
	{ "FloorItem"		, 13	}
};
std::string ETypeMapReverse(int input) {
	for (auto& x : StringIntEtype) {
		if (x.second == input) { return x.first; }
	}
	throw std::out_of_range("Input to ETypeMapReverse out of range.");
	return "";
}

Sprite* a00() { return new Physical(); }
Sprite* a01() { return new Vessel(); }
Sprite* a02() { return new Tile(); }
Sprite* a03() { return new DeleteBrush(); }
Sprite* a04() { return new Menu(); }
Sprite* a05() { return new MenuB(); }
Sprite* a06() { return new EditorEnt(); }
Sprite* a07() { return new EditorIcon(); }
Sprite* a08() { return new SaveLoadButton(); }
Sprite* a09() { return new SaveButton(); }
Sprite* a10() { return new LoadButton(); }
Sprite* a11() { return new Creature(); }
Sprite* a12() { return new MenuItem(); }
Sprite* a13() { return new FloorItem(); }
Sprite* a14() { return new MousePointer(); }
Sprite* a15() { return new Gun(); }
Sprite* (*entityCreation[])() = { a00, a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11, a12, a13, a14, a15 };

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
	ent->initialize();
	allsprites.add(ent);
	return ent;
}
Sprite* Ents::create(std::string etype)
{
	return create(StringIntEtype[etype]);
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
	MenuHoldingObject = ent;
}
void Ents::addInventoryEntity(Sprite* ent, int index) 
{
	MenuContents[index] = static_cast<MenuItem*>(ent);
}
void Ents::findMouseover() 
{
	SDL_GetMouseState(&app.MouseX, &app.MouseY);
	globals.Mouseover = M_GAME;
	if (globals.ViewMode == V_EDITOR) {
		for (Sprite* v : allbuttons.allsprites) {
			if (vec2d::SquareCollision(v->rect, vec2d(app.MouseX, app.MouseY), 32)) { globals.Mouseover = M_EDITORPANEL; }
		}
	}
}
Sprite* Ents::SIDToEnt(int SID) 
{
	for (Sprite* sprite : allphysicals.allsprites) {
		Physical* psprite = static_cast<Physical*>(sprite);
		if (psprite->getSID() == SID) { return sprite; }
	}
	return nullptr;
}
void Ents::incrementEntCounter() 
{
	entCount += 1;
}
std::vector<std::string> Ents::getAllTable() 
{
	std::vector<std::string> table;
	for (Sprite* sprite : allphysicals.allsprites) {
		Physical* physicalized = static_cast<Physical*>(sprite);
		table.push_back(physicalized->getData());
	}
	return table;
}
void Ents::deleteAll() 
{
	
	int i = 0;
	while (i < std::size(AllParticleLayers)) {
		AllParticleLayers[i]->empty();
		i++;
	}
	if (isValid(MenuContents[0])) { MenuContents[0]->remove(); }
	if (isValid(MenuContents[1])) { MenuContents[1]->remove(); }
	MenuHoldingObject = nullptr;
	MenuContents[0] = nullptr; MenuContents[1] = nullptr;
	allvessels.empty();
	CreatureControlLink = nullptr;
	entCount = 0;
	//for (Sprite* ent : allphysicals.allsprites) {
	//	delete ent;
	//}
	//menulayer1.empty();
	//menulayer2.empty();
	//menulayer3.empty();
	allphysicals.empty(true);
	//allsprites.empty(true);
}
void Ents::remove(Sprite* ent) 
{
	allsprites.remove(ent);
	allphysicals.remove(ent);
	int i = 0;
	while (i < AllParticleLayers.size()) {
		AllParticleLayers[i]->remove(ent);
		i++;
	}
	allvessels.remove(ent);
	if (CreatureControlLink == ent) { CreatureControlLink = nullptr; }
}
void Ents::removeUI(Sprite* ent) 
{
	allsprites.remove(ent);
	menulayer1.remove(ent);
	menulayer2.remove(ent);
	menulayer3.remove(ent);
}

int Ents::getEntCount()
{
	return entCount;
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

bool isValid(Sprite* sprite)
{
	if (sprite == nullptr || sprite == NULL) {
		return false;
	}
	else {
		if (sprite->removing == false) {
			return true;
		}
		else {
			return false;
		}
	}
}

std::string data_number_node(std::string datapeice) 
{
	return "[" + std::to_string(std::size(datapeice)) + "]" + datapeice;
}