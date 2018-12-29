#include "HUD.hpp"

void RenderHUD()
{
    // Text
    font = TTF_OpenFont("determinationmonoweb-webfont.ttf", 72);
    SDL_Color black = {0, 0, 0};
    std::string text = "Floor " + std::to_string(level);
    surface = TTF_RenderText_Solid(font, text.c_str(), black);
    message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rectT;
    rectT.x = 55;
    rectT.y = 20;
    rectT.w = surface->w;
    rectT.h = surface->h;

    // Rectangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
    SDL_Rect rectR;
    rectR.x = 5;
    rectR.y = 5;
    rectR.w = rectT.w+100;
    rectR.h = rectT.h+30;

    // Draw em
    SDL_RenderFillRect(renderer, &rectR);
    SDL_RenderCopy(renderer, message, NULL, &rectT);

    // Cleanup
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
    TTF_CloseFont(font);
}
