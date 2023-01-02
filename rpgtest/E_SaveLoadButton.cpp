#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "E_SaveLoadButton.h"
#include "Ents.h"
#include "Globals.h"
#include <iostream>
#include <fstream>

	void SaveLoadButton::initialize() {
		ents.menulayer2.add(this);
		ents.allbuttons.add(this);
		viewmode = V_EDITOR;
	}
	void SaveLoadButton::pressed() {
	
	}
	void SaveLoadButton::onTick() {
		if (viewmode == V_EDITOR) {
			
			if (vec2d::SquareCollision(vec2d(rect), vec2d(app.MouseX, app.MouseY), 32)) {
				if (app.mousepressed) {
					std::cout << "Pressed" << std::endl;
					pressed();
				}
			}
		}
	}

	void SaveButton::pressed() {
		std::cout << "Saving..." << std::endl;
		std::vector<std::string> savetable = ents.getAllTable();
		std::string savestring;
		for (std::string table : savetable) {
			savestring = savestring + "{" + table + "}";
		}
		std::ofstream file;
		file.open(app.basepath + "savefile.txt", std::ios::out);
		if (file.is_open()) {
			std::cout << savestring << std::endl;
			file << savestring;
			file.close();
			std::cout << "Saved." << std::endl;
		}
		else {
			std::cout << "File failed to open." << std::endl;
		}
	}

	void LoadButton::pressed() {
		std::cout << "Loading..." << std::endl;
		ents.deleteAll();
		std::fstream file;
		std::string filestring;
		file.open(app.basepath + "savefile.txt", std::ios::in);
		if (file.is_open()) {   
			getline(file, filestring);
			file.close();  
			std::vector<std::vector<std::string>> loadtablesuper;
			std::vector<std::string> loadtable;
			std::string loadtablesub;
			int chunklen = 0;
			std::string chunklenstring;
			int marker = 1;
			int submarker = 0;
			for (char letter : filestring) {
				if (marker == 1) {
					marker = 2;
				}
				else if (marker == 2) {
					if (letter != '}') {
						if (letter == '[') {
							marker = 3;
							chunklen = 0;
							chunklenstring = "";
						}
					}
					else {
						marker = 1;
						loadtablesuper.push_back(loadtable);
						loadtable.clear();
					}
				}
				else if (marker == 3) {
					if (letter != ']') {
						chunklenstring = chunklenstring + letter;
					}
					else {
						marker = 4;
						submarker = 0;
						chunklen = stoi(chunklenstring);
						loadtablesub = "";
					}
				}
				else if (marker == 4) {
					submarker++;
					loadtablesub = loadtablesub + letter;
					if (submarker == chunklen) {
						loadtable.push_back(loadtablesub);
						marker = 2;
					}
				}
			}
			std::vector<Sprite*> spawnedEnts;
			for (std::vector<std::string> table : loadtablesuper) {
				Sprite* ent = ents.create(table[0]);
				Physical* pent = static_cast<Physical*>(ent);
				if (isValid(pent)) {
					pent->calculatePosition();
					pent->setSID(stoi(table[1]));
					spawnedEnts.push_back(ent);
				}
			}
			int i = 0;
			while (i < spawnedEnts.size()) {
				Sprite* ent = spawnedEnts[i];
				std::vector<std::string> table = loadtablesuper[i];
				ent->enterData(table);
				if (ent->classtype == E_Creature) {
					ents.CreatureControlLink = ent;
				}
				i++;
			}
			i = 0;
			while (i < spawnedEnts.size()) {
				Sprite* ent = spawnedEnts[i];
				std::vector<std::string> table = loadtablesuper[i];
				Physical* pent = static_cast<Physical*>(ent);
				if (isValid(pent)) {
					Sprite* other_ent = ents.SIDToEnt(stoi(table[6]));
					pent->setParent(static_cast<Physical*>(other_ent));
				}
				i++;
			}
			std::cout << "Loaded." << std::endl;
		}
		file.close();
	}