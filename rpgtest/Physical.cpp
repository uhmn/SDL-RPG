#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <random>
#include <SDL_ttf.h>
#include <iostream>


#include "Physical.h"
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
	std::cout << "Thingg" << std::endl;
	posOffset.SetToRect(rect);
	cellLayer = -1;
	vesselCell = 0;
	parent = nullptr;
	//ents.incrementEntCounter();
	//id = ents.getEntCount();
	//ents.allparticles.append(this);
}
vec2d Physical::calculatePosition()
{ 
	if (parent != nullptr) {
		position = vec2d::Add(posOffset, parent->calculatePosition());
	}
	else {
		position = posOffset;
	}
	vec2d::SetRectToVector(&rect, position);
	return position;
}
void Physical::removeCellListReference()
{
	if (cellLayer != -1) {
		if (cellLayer > 1) {
			//parent->cellTiles
		}
		else {
			//do something
		}
	}
}
void Physical::update()
{
	calculatePosition();
	posOffset.Add(0.05);
	//calculateVesselCell();
	onTick();

}
void Physical::setPos( vec2d pos )
{
	posOffset = pos;
	calculatePosition();
}
void Physical::applyParent(Physical* newparent)
{
	parent = newparent;
	parent->childs.push_back(this);
	posOffset = vec2d::Round(vec2d::Sub(position, parent->position));
}
void Physical::setParent(Physical* newparent)
{
	if (parent != nullptr) {
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
		//calculateVesselCell();
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
void Physical::remove()
{
	//ents.remove(this);
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
		if (parent->classtype == 69420) {
			//removeCellListReference();
		}
	}
}
void Physical::onTick() {}
void Physical::initialize() {/*ents.floorlayer.add(this);*/ }

