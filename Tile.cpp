
#include <SDL_mixer.h>
#include "Tile.h"
#include "SDL_mixer_function.h"

using namespace std;
void Tile::render() {
    render_empty();
    SDL_Surface* image = NULL;
    switch (mark) {
    case 1:
        status = Tile_Status::Candy1;
        image = IMG_Load("image/candy1.png");
        break;
    case 2:
        status = Tile_Status::Candy2;
        image = IMG_Load("image/candy2.png");
        break;
    case 3:
        status = Tile_Status::Candy3;
        image = IMG_Load("image/candy3.png");
        break;

    case 4:
        status = Tile_Status::Candy4;
        image = IMG_Load("image/candy4.png");
        break;
    case 5:
        status = Tile_Status::Candy5;
        image = IMG_Load("image/candy5.png");
        break;
    default:
        break;
    }
    if (image == NULL)
    {
        cerr << "Unable to load image! SDL Error: " << SDL_GetError();
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, image); //
         SDL_SetTextureAlphaMod(texture, 255);
         SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }
    SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
    SDL_RenderPresent(renderer);
}
void Tile::render_selected() {
    SDL_Surface* image = NULL;
    image = IMG_Load("image/select.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image); //
    SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
    SDL_RenderPresent(renderer);
}
void Tile::render_empty() {
    SDL_Surface* image = NULL;
    switch (colour) {
    case Tile_empty::LightEmpty:
        image = IMG_Load("image/today.png");
        break;
    case Tile_empty::DarkEmpty:
        image = IMG_Load("image/today.png");
        break;
    }
    if (image == NULL)
    {
        cerr << "Unable to load image! SDL Error: " << SDL_GetError();
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image); //
        SDL_RenderCopy(renderer, texture, NULL, &Tile_rect);
    }
}
void Tile::swapTile(Tile otherTile, SDL_Texture* MoveText, int speed) {
    SDL_Rect thisRect = Tile_rect;
    SDL_Rect otherRect = otherTile.Tile_rect;
    for (; otherRect.y != Tile_rect.y ;) {
        if (MoveText != NULL) {
            otherRect.y += speed;
            if (otherRect.y > Tile_rect.y) otherRect.y = Tile_rect.y;
        }
        else if (otherTile.Tile_rect.y > Tile_rect.y) {
            otherRect.y -= 7; thisRect.y += 7;
        }
        else {
            otherRect.y += 7; thisRect.y -= 7;
        }
        if (MoveText == NULL) {
            SDL_RenderCopy(renderer, texture, NULL, &thisRect);
            SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        }
        else {
            SDL_RenderCopy(renderer, MoveText, NULL, &otherRect);
        }
        SDL_RenderPresent(renderer);
        otherTile.render_empty();
        render_empty();
    }
    for (; otherRect.x != Tile_rect.x;) {
        if (otherTile.Tile_rect.x > Tile_rect.x) {
            otherRect.x -= 7; thisRect.x += 7;
        }
        else {
            otherRect.x += 7; thisRect.x -= 7;
        }
        SDL_RenderCopy(renderer, texture, NULL, &thisRect);
        SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        SDL_RenderPresent(renderer);
        otherTile.render_empty();
        render_empty();
    }
}