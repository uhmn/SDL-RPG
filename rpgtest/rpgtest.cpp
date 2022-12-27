#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
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

int main(int argc, char* argv[])
{
    WINDOW_HEIGHT = 600;
    WINDOW_WIDTH = 800;
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

    Sprite* phys1 = ents.create(E_Physical);
    Physical* phys1c = static_cast<Physical*>(phys1);
    phys1c->setPos(vec2d(300, 300));

    Sprite* ves1 = ents.create(E_Vessel);
    Physical* ves1v = static_cast<Physical*>(ves1);
    ves1v->setPos(vec2d(390, 366));

    phys1c->setParent(ves1v);

    EditorEnt* editorbrush = static_cast<EditorEnt*>(ents.create(E_EditorEnt));
    editorbrush->setParent(ves1v);

    ents.EditBrush = editorbrush;

    while (!globals.GameQuit)
    {
        SDL_RenderClear(app.Renderer);
        doInput();
        ents.update();
        ents.draw(app.Renderer);
        SDL_RenderPresent(app.Renderer);
        SDL_Delay(17);
    }

    SDL_DestroyRenderer(app.Renderer);
    SDL_DestroyWindow(app.Window);

    SDL_Quit();
    return 0;
}
