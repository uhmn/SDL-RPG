#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <random>
#include <iostream>


#include "E_Physical.h"
#include "Globals.h"
#include "Ents.h"

void Testing() {
	std::cout << GRandom(1, 100) << std::endl;
	vec2d th1(0,0);
	vec2d th2(0.2, 0.6);
	vec2d::Distance(th1, th2);
}



Physical::Physical() : Sprite(0, 0, 32, 32, "strawberry.png") {}
void Physical::start()
{
	posOffset.SetToRect(rect);
	cellLayer = -1;
	vesselCell = 0;
	parent = nullptr;
	ents.incrementEntCounter();
	id = ents.getEntCount();
	ents.allphysicals.add(this);
	lastVessel = nullptr;

}
vec2d Physical::calculatePosition()
{ 
	if (parent != nullptr) {
		position = vec2d::Add(posOffset, parent->calculatePosition());
	}
	else {
		position = posOffset;
	}
	if (ents.CreatureControlLink != this || globals.ViewMode != V_1ST) {
		vec2d pos2 = vec2d::Sub(position, vec2d(globals.CamX, globals.CamY));
		vec2d::SetRectToVector(&rect, pos2);
	}
	else {
		rect.x = WINDOW_WIDTH / 2;
		rect.y = WINDOW_HEIGHT / 2;
	}
	return position;
}
void Physical::removeCellListReference()
{
	if (cellLayer != -1) {
		Vessel* vparent = static_cast<Vessel*>(parent);
		std::vector<Physical*, std::allocator<Physical*>> vcelllocation = vparent->cellTiles[vesselCell];
		
		if (cellLayer > 1) {
			vcelllocation.erase(vcelllocation.begin() + cellLayer);
		}
		else {
			vcelllocation[cellLayer] = nullptr;
		}
	}
}
void Physical::calculateVesselCell() 
{
	if (parent != nullptr && classtype != E_Tile) {
		if (lastVessel != nullptr) {
		removeCellListReference();
		}
		if (parent->classtype == E_Vessel) {
			vesselCell = ents.findCellIndexOfPos(position, parent->position, 25);
			Vessel* vparent = static_cast<Vessel*>(parent);
			vparent->cellTiles[vesselCell].push_back(this);
		}
		else {
			vesselCell = parent->vesselCell;
		}
	}
}
void Physical::update()
{
	//std::cout << "Physical update" << std::endl;
	calculatePosition();
	calculateVesselCell();
	onTick();
	if (removing != false) { return; }
	calculatePosition();
}
void Physical::setPos( vec2d pos )
{
	posOffset = pos;
	calculatePosition();
}
void Physical::setPosOffset(vec2d pos)
{
	posOffset = pos;
	calculatePosition();
	//vec2d pos2 = vec2d::Sub(position, vec2d(globals.CamX, globals.CamY));
	//vec2d::SetRectToVector(&rect, pos2);
	//std::cout << "setpos" << std::endl;
}
void Physical::applyParent(Physical* newparent)
{
	parent = newparent;
	parent->childs.push_back(this);
	posOffset = vec2d::Round(vec2d::Sub(position, parent->position));
	
}
void Physical::setParent(Physical* newparent)
{
	if (newparent != nullptr) {
		applyParent(newparent);
	}
	else {
		parent = nullptr;
	}
}
void Physical::unParent()
{
	if (parent != nullptr) {
		Physical* newparent = parent->parent;
		setParent(newparent);
		calculateVesselCell();
	}
	posOffset = position;
}
void Physical::setSprite(std::string image1)
{
	updateSurface(image1);
}
unsigned int Physical::getID()
{
	return id;
}
void Physical::setSID(int nsid)
{
	sid = nsid;
}
int Physical::getSID()
{
	return sid;
}
void Physical::remove()
{
	ents.remove(this);
	for (Physical* ent : childs) {
		ent->unParent();
	}
	if (parent != nullptr) {
		int return_i = -1;
		int i = 0;
		for (Physical* v : parent->childs)
		{
			if (v == this)
			{
				return_i = i;
			}
			i += 1;
		}
		if (return_i != -1)
		{
			parent->childs.erase(parent->childs.begin() + return_i);
		}
		if (parent->classtype == E_Vessel) {
			removeCellListReference();
		}
	}
	deconstructSelf();
}
void Physical::checkShipCollisions() {
	if (isValid(parent) == false) {
		Sprite* block = ents.findBlocksAt(position, nullptr).first;
		Physical* pblock = static_cast<Physical*>(block);
		if (isValid(parent) == false && isValid(pblock) == true) {
			setParent(pblock->parent);
			if (static_cast<Sprite*>(this)->classtype == E_Creature) { setPosOffset(pblock->posOffset); }
		}
	}
	else {
		if (static_cast<Sprite*>(parent)->classtype == E_Vessel && isValid(ents.findBlocksAt(position, static_cast<Vessel*>(parent)).first) == false) {
			unParent();
		}
	}
}
Physical* Physical::getVessel()
{
	if (getClassType() == E_Vessel) {
		return this;
	}
	else {
		if (isValid(parent)) {
			parent->getVessel();
		}
		else {
			return nullptr;
		}
	}
}
void Physical::enterData(std::vector<std::string> data)
{
	setSprite(data[2]);
	posOffset = (vec2d(stod(data[3]), stod(data[4])));
	calculatePosition();
}
std::string Physical::getData()
{
	int localparent = 0;
	if (isValid(parent)) {
		localparent = static_cast<Physical*>(parent)->getID();
	}
	std::string answer;
	answer = data_number_node(ETypeMapReverse(classtype));
	answer = answer + data_number_node(std::to_string(id));
	answer = answer + data_number_node(imagename);
	answer = answer + data_number_node(std::to_string(posOffset.x));
	answer = answer + data_number_node(std::to_string(posOffset.y));
	answer = answer + data_number_node("S1SIIS1");
	answer = answer + data_number_node(std::to_string(localparent));
	return answer;
}
void Physical::onTick() {}
void Physical::initialize() { ents.floorlayer.add(this); }



