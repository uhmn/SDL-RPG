#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "MathFunctionsHeader.h"
#include "Globals.h"

std::string TileSprites[13][3] = {  {"strawberry.png", "2", "0"},
                                    {"wall.png", "2", "1"},
                                    {"wall2.png", "2", "1"},
                                    {"wall3.png", "2", "1"},
                                    {"grate.png", "2", "0"},
                                    {"girderwallLR.png", "2", "1"},
                                    {"girderwallUD.png", "2", "1"},
                                    {"girderwallLRUD.png", "2", "1"},
                                    {"deletebrush.png", "3", "0"},
                                    {"thrusterL.png", "Thruster", "1"},
                                    {"thrusterR.png", "Thruster", "1"},
                                    {"thrusterU.png", "Thruster", "1"},
                                    {"thrusterD.png", "Thruster", "1"},
};

int WINDOW_HEIGHT;
int WINDOW_WIDTH;

App app;
Globals globals;

void doKeyHold()
{
    if (app.up == 1)
    {
        //c[0].yl = c[0].yl + 10;
    }
    if (app.down == 1)
    {
        //c[0].yl = c[0].yl - 10;
    }
    if (app.left == 1)
    {
        // c[0].xl = c[0].xl + 10;
    }
    if (app.right == 1)
    {
        //c[0].xl = c[0].xl - 10;
    }
    if (app.w == 1)
    {
        //c[0].zl = c[0].zl + 10;
    }
    if (app.s == 1)
    {
        //c[0].zl = c[0].zl - 10;
    }
}

void doKeyUp(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            app.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            app.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            app.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            app.right = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            app.w = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            app.s = 0;
        }
    }
}

void doKeyDown(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_END)
        {
            std::cout << "Quitted" << std::endl;
            globals.GameQuit = true;
        }
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            app.up = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            app.down = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            app.left = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            app.right = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            app.w = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            app.s = 1;
        }
    }
}

void doInput(void)
{
    SDL_Event event;
    SDL_GetMouseState(&app.MouseX, &app.MouseY);

    app.mousepressed = 0;
    while (SDL_PollEvent(&event))
    {
        
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_MOUSEBUTTONDOWN:
            app.mouseheld = 1;
            app.mousepressed = 1;
            break;

        case SDL_MOUSEBUTTONUP:
            app.mouseheld = 0;
            break;

        case SDL_KEYDOWN:
            doKeyDown(&event.key);
            break;

        case SDL_KEYUP:
            doKeyUp(&event.key);
            break;

        default:
            break;
        }
    }
}