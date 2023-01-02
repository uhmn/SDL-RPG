#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include "MathFunctionsHeader.h"
#include "Globals.h"
#include "Ents.h"

std::string TileSprites[13][3] = {  {"strawberry.png", "2", "0"},
                                    {"wall.png", "2", "1"},
                                    {"wall2.png", "2", "1"},
                                    {"wall3.png", "2", "1"},
                                    {"grate.png", "2", "0"},
                                    {"girderwallLR.png", "2", "1"},
                                    {"girderwallUD.png", "2", "1"},
                                    {"girderwallLRUD.png", "2", "1"},
                                    {"deletebrush.png", "3", "0"},
                                    {"thrusterL.png", "2", "1"},
                                    {"thrusterR.png", "2", "1"},
                                    {"thrusterU.png", "2", "1"},
                                    {"thrusterD.png", "2", "1"},
};

int WINDOW_HEIGHT;
int WINDOW_WIDTH;

App app;
Globals globals;

void doKeyHold()
{
    Creature* CreatureControlLinkPhysical = static_cast<Creature*>(ents.CreatureControlLink);
    int keysPressed = 0;
    if (app.up == 1)
    {
        keysPressed++;
    }
    if (app.down == 1)
    {
        keysPressed++;
    }
    if (app.left == 1)
    {
        keysPressed++;
    }
    if (app.right == 1)
    {
        keysPressed++;
    }
    if (globals.ViewMode == V_EDITOR) {
        if (app.up == 1)
        {
            globals.CamY = globals.CamY - (16 / (keysPressed / (keysPressed / 1.5)));
        }
        if (app.down == 1)
        {
            globals.CamY = globals.CamY + (16 / (keysPressed / (keysPressed / 1.5)));
        }
        if (app.left == 1)
        {
            globals.CamX = globals.CamX - (16 / (keysPressed / (keysPressed / 1.5)));
        }
        if (app.right == 1)
        {
            globals.CamX = globals.CamX + (16 / (keysPressed / (keysPressed / 1.5)));
        }
    }
    else if (globals.ViewMode == V_1ST && isValid(CreatureControlLinkPhysical)) {
        
        if (CreatureControlLinkPhysical->moveCooldown > 0) {
            float movecooldown = static_cast<float>(CreatureControlLinkPhysical->moveCooldown);
            float lastmovecooldown = static_cast<float>(CreatureControlLinkPhysical->lastMoveCooldown);
            double slider = movecooldown / lastmovecooldown;
            globals.CamX = slider * (CreatureControlLinkPhysical->lastPosition.x-WINDOW_WIDTH/2)+(1-slider)*(CreatureControlLinkPhysical->position.x-WINDOW_WIDTH/2);
            globals.CamY = slider * (CreatureControlLinkPhysical->lastPosition.y-WINDOW_HEIGHT/2)+(1-slider)*(CreatureControlLinkPhysical->position.y-WINDOW_HEIGHT/2);
        }
        else {
            globals.CamX = (CreatureControlLinkPhysical->position.x) - WINDOW_WIDTH / 2;
            globals.CamY = (CreatureControlLinkPhysical->position.y) - WINDOW_HEIGHT / 2;
        }
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
        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            app.a = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            app.d = 0;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RETURN)
        {
            app.enter = 0;
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
        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            app.a = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            app.d = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RETURN)
        {
            if (globals.ViewMode == V_1ST) {
                globals.ViewMode = V_EDITOR;
            }
            else if (globals.ViewMode == V_EDITOR) {
                globals.ViewMode = V_1ST;
            }
            app.enter = 1;
        }
    }
}

void doInput(void)
{
    doKeyHold();

    SDL_Event event;
    
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