#include "E_EditorIcon.h"
#include "Ents.h"
#include "Globals.h"

void EditorIcon::initialize() {
	ents.menulayer2.add(this);
	ents.allbuttons.add(this);
	viewmode = V_EDITOR;
}
void EditorIcon::setSprite(std::string image1) {
	updateSurface(image1);
}
void EditorIcon::setproperties(int offset) {
	tileoffset = offset;
	enttype = stoi(TileSprites[offset][1]);
	setSprite(TileSprites[offset][0]);
}
void EditorIcon::onTick() {
	if (viewmode == V_EDITOR) {
		if (vec2d::Collision(vec2d(rect.x - 16, rect.y - 16),
							 vec2d(rect.x + 16, rect.y + 16),
							 vec2d(app.MouseX, app.MouseY))) {
			if (app.mousepressed) {
				ents.EditorType = imagename;
				ents.EditorEntType = enttype;
				ents.EditorTileOffset = tileoffset;
				ents.EditBrush->setSprite(ents.EditorType);
			}
		}
	}
}