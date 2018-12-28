#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ECS.hpp"

#define WIN_WIDTH 1600
#define WIN_HEIGHT WIN_WIDTH
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

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
