#include "globals.hpp"

bool running = true;
SDL_Window* window;
SDL_Renderer* renderer;
Keyboard KB;

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
