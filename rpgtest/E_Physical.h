#pragma once
#include "MathFunctionsHeader.h"
#include "SpriteBase.h"
#include "Vectors.h"
#include <vector>
#include <string>
void Testing();


class Physical : public Sprite {
public:
	vec2d posOffset;
	Physical* parent;
	unsigned int id;
	unsigned int sid;
	std::vector<Physical*> childs;
	vec2d position;
	unsigned int vesselCell;
	int cellLayer;
	unsigned int classtype;
	Physical* lastVessel;

	Physical();
	virtual void start();
	vec2d calculatePosition();
	void removeCellListReference();
	void calculateVesselCell();
	virtual void update();
	void setPos(vec2d pos);
	void setPosOffset(vec2d pos);
	virtual void applyParent(Physical* newparent);
	void setParent(Physical* newparent);
	void unParent();
	virtual void setSprite(std::string image1);
	unsigned int getID();
	void setSID(int nsid);
	int getSID();
	void remove();
	void checkShipCollisions();
	Physical* getVessel();
	virtual void onTick();
	virtual void initialize();
	virtual void enterData(std::vector<std::string> data);
	virtual std::string getData();
};

