#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_Mixer.h>
#include <random>
#include <SDL_ttf.h>
#include <iostream>

#include <windows.h>
#include <limits.h>
#include <atlstr.h>

#include "MathFunctionsHeader.h"
#include "Globals.h"
#include "MathFunctions.h"
#include "SpriteBase.h"
#include "Ents.h"
#include "Sound.h"

int main(int argc, char* argv[])
{
    globals.gravity = 9.8;
    WINDOW_HEIGHT = 480;
    WINDOW_WIDTH = 1280;
    TTF_Init();
    app.MainFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 25);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    app.Window = SDL_CreateWindow("2D Game Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    app.Renderer = SDL_CreateRenderer(app.Window, -1, render_flags);

    globals.ViewMode = V_EDITOR;
    globals.Mouseover = M_GAME;

    ents.create(E_MousePointer);
    
    Sprite* ves1 = ents.create(E_Vessel);
    Physical* ves1v = static_cast<Physical*>(ves1);
    ves1v->setPos(vec2d(390, 366));

    Creature* plytest = static_cast<Creature*>(ents.create(E_Creature));
    plytest->setPos(vec2d(532, 400));
    plytest->setParent(ves1v);
    ents.CreatureControlLink = plytest;
    
    //phys1c->setParent(ves1v);
    
    EditorEnt* editorbrush = static_cast<EditorEnt*>(ents.create(E_EditorEnt));
    editorbrush->setParent(ves1v);
    
    ents.EditBrush = editorbrush;

    Menu* panel1 = static_cast<Menu*>(ents.create(E_Menu));
    panel1->setSprite("smallmenubox.png");
    panel1->setViewMode(V_1ST);
    panel1->setPosDimensionless(vec2d(0.5, 0.9));
    MenuB* panel1text = static_cast<MenuB*>(ents.create(E_MenuB));
    panel1text->setSprite("lefthandText.png");
    panel1text->setViewMode(V_1ST);
    panel1text->setPosDimensionless(vec2d(0.5, 0.9));

    Menu* panel2 = static_cast<Menu*>(ents.create(E_Menu));
    panel2->setSprite("smallmenubox.png");
    panel2->setViewMode(V_1ST);
    panel2->setPosDimensionless(vec2d(0.56, 0.9));
    MenuB* panel2text = static_cast<MenuB*>(ents.create(E_MenuB));
    panel2text->setSprite("righthandText.png");
    panel2text->setViewMode(V_1ST);
    panel2text->setPosDimensionless(vec2d(0.56, 0.9));

    int load_iter = 0;
    for (std::string* iter : TileSprites) {
        EditorIcon* ico = static_cast<EditorIcon*>(ents.create(E_EditorIcon));
        ico->setproperties(load_iter);
        ico->setPosDimensionless(vec2d(0.55 + (load_iter * 0.03), 0.85));
        load_iter++;
    }

    SaveButton* sbutton = static_cast<SaveButton*>(ents.create(E_SaveButton));
    sbutton->setSprite("save.png");
    sbutton->setPosDimensionless(vec2d(0.1, 0.05));

    LoadButton* lbutton = static_cast<LoadButton*>(ents.create(E_LoadButton));
    lbutton->setSprite("load.png");
    lbutton->setPosDimensionless(vec2d(0.15, 0.05));

    ents.MenuPositions[0] = vec2d(panel1->rect); ents.MenuPositions[1] = vec2d(panel2->rect);
    ents.HotbarSprites[0] = panel1; ents.HotbarSprites[1] = panel2;

    FloorItem* testitem = static_cast<FloorItem*>(ents.create(E_FloorItem));
    testitem->setSprite("woodbox.png");
    testitem->putInside(plytest, 0);

    FloorItem* testitem2 = static_cast<FloorItem*>(ents.create(E_Gun));
    testitem2->putInside(plytest, 1);
    while (!globals.GameQuit)
    {
        SDL_RenderClear(app.Renderer);
        ents.findMouseover();
        ents.update();
        doInput();
        ents.draw(app.Renderer);
        SDL_RenderPresent(app.Renderer);
        SDL_Delay(17);
    }

    ents.deleteAll();
    SDL_DestroyRenderer(app.Renderer);
    SDL_DestroyWindow(app.Window);

    SDL_Quit();
    return 0;
}
