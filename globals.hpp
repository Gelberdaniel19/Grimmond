#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "ECS.hpp"
#include "colors.hpp"

#define WIN_WIDTH 1600
#define WIN_HEIGHT WIN_WIDTH
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

extern RGBColor* bgColor;
extern RGBColor* cloudColor;

extern int level;

struct Camera
{
    float x = 0;
    float y = 0;
    float width = 1500;
    float height = 1500;

    float ScaleWidth(float w2);
    float ScaleHeight(float h2);
    float TransformX(float x2);
    float TransformY(float y2);
}; extern Camera Cam;

extern bool running;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern SDL_Surface* surface;
extern SDL_Texture* message;

struct Keyboard
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
}; extern Keyboard KB;


void HandleInput();
