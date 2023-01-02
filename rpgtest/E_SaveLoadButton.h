#pragma once
#include "E_Menu.h"


class SaveLoadButton : public Menu {
public:
	void initialize();
	virtual void pressed();
	void onTick();
};

class SaveButton : public SaveLoadButton {
public:
	void pressed();
};

class LoadButton : public SaveLoadButton {
public:
	void pressed();
};