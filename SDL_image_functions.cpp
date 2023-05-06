
#include "SDL_image_functions.h"

void Show_image(SDL_Renderer* renderer, const char* str_image, SDL_Rect rect)
{
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface* surface = IMG_Load(str_image);
    if (surface == NULL)
    {
        cerr << "Unable to load image " << str_image << "! SDL Error: " << SDL_GetError() << endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);//
    if (texture == NULL)
    {
        cerr << "Unable to create texture from " << str_image << "! SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    IMG_Quit();
}