#pragma once
#include "SpriteBase.h"
#include "Vectors.h"
#include "E_Physical.h"

class EditorEnt : public Physical {
	void initialize();
	void onTick();
};