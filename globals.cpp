#include "globals.hpp"

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer;
Keyboard KB;
Camera Cam;
RGBColor* bgColor;
RGBColor* cloudColor;

float Camera::ScaleWidth(float w2)
{
    return (WIN_WIDTH * w2 / width)+1;
}
float Camera::ScaleHeight(float h2)
{
    return (WIN_HEIGHT * h2 / height)+1;
}
float Camera::TransformX(float x2)
{
    return ((x2-x) * WIN_WIDTH / width);
}
float Camera::TransformY(float y2)
{
    return ((y2-y) * WIN_HEIGHT / height);
}

void HandleInput()
{
	SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
		case SDL_QUIT:
			running = false;
			break;

        int key;
        case SDL_KEYDOWN:
            key = e.key.keysym.sym;
            if (key == SDLK_UP || key == SDLK_w)
	            KB.up = true;
			if (key == SDLK_DOWN || key == SDLK_s)
                KB.down = true;
            if (key == SDLK_LEFT || key == SDLK_a)
                KB.left = true;
            if (key == SDLK_RIGHT || key == SDLK_d)
                KB.right = true;
			break;

        case SDL_KEYUP:
            key = e.key.keysym.sym;
            if (key == SDLK_UP || key == SDLK_w)
	            KB.up = false;
			if (key == SDLK_DOWN || key == SDLK_s)
                KB.down = false;
            if (key == SDLK_LEFT || key == SDLK_a)
                KB.left = false;
            if (key == SDLK_RIGHT || key == SDLK_d)
                KB.right = false;
			break;
        }
    }
}
