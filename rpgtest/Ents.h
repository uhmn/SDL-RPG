#pragma once
#include "E_Physical.h"
#include "E_Vessel.h"
#include "E_Tile.h"
#include "E_Menu.h"
#include "E_EditorEnt.h"
#include "E_EditorIcon.h"

struct SpritePair
{
	Sprite* first;
	Sprite* second;
	SpritePair(Sprite* firstinput, Sprite* secondinput);
	Sprite* take(bool selection);
};

class Ents
{
private:
	spritelist allsprites;
	std::vector<spritelist*> AllParticleLayers;
	Sprite* CreatureControlLink;
	Sprite* MenuHoldingObject;
	vec2d MenuPositions[2];
	Sprite* HotbarSprites[2];
	Sprite* MenuContents[2];
	unsigned int entCount;
public:
	spritelist floorlayer;
	spritelist walllayer;
	spritelist midlayer;
	spritelist playerlayer;
	spritelist playercosmeticlayer;
	spritelist editlayer;

	spritelist menulayer1;
	spritelist menulayer2;
	spritelist menulayer3;
	spritelist allvessels;
	spritelist allbuttons;
	spritelist allphysicals;

	std::string EditorType;
	int EditorTileOffset;
	int EditorEntType;
	EditorEnt* EditBrush;

	Ents();
	//void getEntityTypes();
	Sprite* create(unsigned int etype);
	void update();
	void draw(SDL_Renderer* renderer);
	int findCellIndexOfPos(vec2d pos, vec2d vesselPos, unsigned int cellSize);
	Sprite* findEntAtCellIndex(int cellIndex, Vessel* vessel, int layer);
	SpritePair findBlocksAt(vec2d pos, Vessel* vessel);
	void setMenuHoldingObject(Sprite* ent);
	void addInventoryEntity(Sprite* ent, int index);
	void findMouseover();
	Sprite* SIDToEnt(int SID);
	void incrementEntCounter();
	//SaveData* getAllTable();
	void deleteAll();
	void remove(Sprite* ent);
	void removeUI(Sprite* ent);
};

vec2d MousePosToGridPos(double parentX, double parentY);
vec2d MousePosToVesselPos(double parentX, double parentY);
vec2d MousePosToPosition(Physical* parent);

#define E_Physical 0
#define E_Vessel 1
#define E_Tile 2
#define E_DeleteBrush 3
#define E_Menu 4
#define E_MenuB 5
#define E_EditorEnt 6
#define E_EditorIcon 7

extern Ents ents;
extern Sprite* (*entityCreation[])();
