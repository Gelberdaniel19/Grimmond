#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine/ECS.hpp"

#define WIN_WIDTH 1600
#define WIN_HEIGHT WIN_WIDTH

extern bool running;
extern SDL_Window* window;
extern SDL_Renderer* renderer;

struct Keyboard
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
}; extern Keyboard KB;


void HandleInput();
