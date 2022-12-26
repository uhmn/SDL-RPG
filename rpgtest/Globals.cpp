#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "MathFunctionsHeader.h"
#include "Globals.h"



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

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
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