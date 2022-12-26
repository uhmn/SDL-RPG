#pragma once
#include "MathFunctionsHeader.h"
#include "SpriteBase.h"
#include "Vectors.h"
void Testing();


class Physical : public Sprite {
public:
	vec2d posOffset;
	Physical* parent;
	unsigned int id;
	std::vector<Physical*> childs;
	vec2d position;
	unsigned int vesselCell;
	int cellLayer;
	unsigned int classtype;
	Physical();
	void start();
	vec2d calculatePosition();
	void removeCellListReference();
	void update();
	void setPos(vec2d pos);
	void applyParent(Physical* newparent);
	void setParent(Physical* newparent);
	void unParent();
	void setSprite(std::string image1);
	unsigned int getID();
	void remove();
	virtual void onTick();
	virtual void initialize();
};

