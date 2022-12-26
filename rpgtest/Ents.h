#pragma once


class Ents
{
private:
	spritelist allsprites;
	//spritelist menulayer1;
	//spritelist menulayer2;
	//spritelist menulayer3;
	//spritelist allvessels;
	//spritelist allbuttons;
	spritelist allphysicals;
	std::vector<spritelist> AllParticleLayers;
	Sprite* CreatureControlLink;
	Sprite* MenuHoldingObject;
	vec2d MenuPositions[2];
	Sprite* HotbarSprites[2];
	Sprite* MenuContents[2];
	std::string EditorType;
	int EditorTileOffset;
	std::string EditorEntType;
	Sprite* EditBrush;
	unsigned int entCount;
	//std::vector<Physical*> floorlayer;
	//std::vector<Physical*> walllayer;
	//std::vector<Physical*> midlayer;
	//std::vector<Physical*> playerlayer;
	//std::vector<Physical*> playercosmeticlayer;
	//std::vector<Physical*> editlayer;
public:
	

	Ents();
	//void getEntityTypes();
	Sprite* create(unsigned int etype);
	void update();
	void draw(SDL_Renderer* renderer);
	int findCellIndexOfPos(vec2d pos, vec2d vesselPos, unsigned int cellSize);
	Sprite* findEntAtCellIndex(int cellIndex, Sprite* vessel, int layer);
	Sprite* findBlocksAt(vec2d pos, Sprite* vessel);
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

extern Ents ents;
extern Sprite* (*functptr[])();