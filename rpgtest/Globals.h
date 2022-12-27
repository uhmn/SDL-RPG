#pragma once
void doInput(void);

struct App {
    unsigned int up;
    unsigned int down;
    unsigned int left;
    unsigned int right;
    unsigned int w;
    unsigned int s;
    unsigned int mouseheld;
    unsigned int mousepressed;
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
    int CamX;
    int CamY;
};

extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

enum viewmode { V_ALL, V_1ST, V_EDITOR };
enum mouseover { M_NONE, M_EDITORPANEL, M_GAME };

extern std::string TileSprites[13][3];

extern Globals globals;
extern App app;