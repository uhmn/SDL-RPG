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
#include "Physical.h"

int WINDOW_HEIGHT = 600;
int WINDOW_WIDTH = 800;

std::wstring ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

int main(int argc, char* argv[])
{
    TTF_Init();
    app.MainFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 25);
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    app.Window = SDL_CreateWindow("F-Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    app.Renderer = SDL_CreateRenderer(app.Window, -1, render_flags);

    std::string Atex = "IMG_1314.png";
    Sprite* dest = SpriteManager.makeSprite(Atex, (WINDOW_WIDTH - 6) / 2, (WINDOW_HEIGHT - 6) / 2, 6, 6);
    Sprite* back = SpriteManager.makePhysical(300, 300); //Atex, -60, 0, WINDOW_WIDTH + 100, WINDOW_HEIGHT + 100
    Sprite* pipe = SpriteManager.makeSprite(Atex, WINDOW_WIDTH + 150, GRandom(180, WINDOW_HEIGHT - 100), 150, 4000);
    Sprite* coin = SpriteManager.makeSprite("Grenade_proj_red.png", 300, 300, 15, 15);
    Sprite* bad = SpriteManager.makeSprite("Grenade_proj_red.png", 10, 10, 17, 17);
    Sprite* bird = SpriteManager.makeSprite(Atex, 0, 0, 10, 10);
    SDL_Color color = { 255, 255, 255 };
    Sprite* text1 = SpriteManager.makeText("Blbabab3", app.MainFont, color, 0, 0);
    Sprite* text2 = SpriteManager.makeSprT("Blbabab3", app.MainFont, color, 50, 50);
    Sprite* text3 = SpriteManager.makeText("Blbabab3", app.MainFont, color, 75, 160);

    std::cout << "my directory is " << app.datapath.append(back->imagename) << "\n";
    Testing();

    while (!globals.GameQuit)
    {
        doInput();
        SpriteManager.update();
        SpriteManager.draw(app.Renderer);
        SDL_RenderPresent(app.Renderer);
        SDL_Delay(17);
    }
    SpriteManager.empty();

    SDL_DestroyRenderer(app.Renderer);
    SDL_DestroyWindow(app.Window);

    SDL_Quit();
    return 0;
}
