#pragma once
void doInput(void);

struct App {
    unsigned int up;
    unsigned int down;
    unsigned int left;
    unsigned int right;
    unsigned int w;
    unsigned int s;
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Surface* Surface;
    TTF_Font* MainFont;
    std::string basepath = SDL_GetBasePath();
    std::string datapath = basepath.append("Data\\");
};

struct Globals {
    bool GameQuit;
};

extern Globals globals;
extern App app;