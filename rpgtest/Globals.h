#pragma once
#include "Vectors.h"
#include "E_MenuItem.h"
void doInput(void);

struct App {
    unsigned int up;
    unsigned int down;
    unsigned int left;
    unsigned int right;
    unsigned int w;
    unsigned int s;
    unsigned int a;
    unsigned int d;
    unsigned int mouseheld;
    unsigned int mousepressed;
    unsigned int enter;
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Surface* Surface;
    TTF_Font* MainFont;
    std::string basepath = SDL_GetBasePath();
    std::string datapath = basepath.append("Data\\");
    int MouseX;
    int MouseY;
};

struct Globals {
    bool GameQuit;
    unsigned int ViewMode;
    unsigned int Mouseover;
    double CamX;
    double CamY;
    vec2d windowSize;
    double gravity;
    MenuItem* ActiveMenuItem;
};

extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

enum viewmode { V_ALL, V_1ST, V_EDITOR };
enum mouseover { M_NONE, M_EDITORPANEL, M_GAME };

extern std::string TileSprites[13][3];

extern Globals globals;
extern App app;