#include "globals.hpp"
#include "Room.hpp"
#include "Level.hpp"
#include "World.hpp"

// DELETE this
#include "Colors.hpp"

int main()
{
	// DELETE THIS
	std::vector<RGBColor*> pair = GenRGBPair();
	std::cout << pair[0]->r << " " << pair[0]->g << " " << pair[0]->b << std::endl;
	std::cout << pair[1]->r << " " << pair[1]->g << " " << pair[1]->b << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("Grimmond", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);

	World world;

	return 0;
}
