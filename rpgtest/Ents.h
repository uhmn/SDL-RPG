#pragma once
#include "E_Physical.h"
#include "E_Vessel.h"
#include "E_Tile.h"
#include "E_Menu.h"
#include "E_EditorEnt.h"
#include "E_EditorIcon.h"
#include "E_SaveLoadButton.h"
#include "E_Creature.h"
#include "E_MenuItem.h"
#include "E_FloorItem.h"
#include "E_MousePointer.h"
#include "E_Gun.h"

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
	std::vector<spritelist*> AllParticleLayers;
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
	spritelist allsprites;

	std::string EditorType;
	int EditorTileOffset;
	int EditorEntType;
	EditorEnt* EditBrush;
	Sprite* CreatureControlLink;
	Sprite* MenuHoldingObject;
	Menu* HotbarSprites[2];
	MenuItem* MenuContents[2];
	vec2d MenuPositions[2];

	Ents();
	//void getEntityTypes();
	Sprite* create(unsigned int etype);
	Sprite* create(std::string etype);
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
	std::vector<std::string> getAllTable();
	void deleteAll();
	void remove(Sprite* ent);
	void removeUI(Sprite* ent);
	int getEntCount();
};

vec2d MousePosToGridPos(double parentX, double parentY);
vec2d MousePosToVesselPos(double parentX, double parentY);
vec2d MousePosToPosition(Physical* parent);
bool isValid(Sprite* sprite);
std::string ETypeMapReverse(int input);
std::string data_number_node(std::string datapeice);

#define E_Physical 0
#define E_Vessel 1
#define E_Tile 2
#define E_DeleteBrush 3
#define E_Menu 4
#define E_MenuB 5
#define E_EditorEnt 6
#define E_EditorIcon 7
#define E_SaveLoadButton 8
#define E_SaveButton 9
#define E_LoadButton 10
#define E_Creature 11
#define E_MenuItem 12
#define E_FloorItem 13
#define E_MousePointer 14
#define E_Gun 15

//extern std::map<std::string, int> StringIntEtype;
extern Ents ents;
extern Sprite* (*entityCreation[])();
