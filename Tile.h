#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

const int Board_row = 6;
const int Board_col = 6;

enum class Tile_Status {
    Empty,
    Candy1,
    Candy2,
    Candy3,
    Candy4,
    Candy5,
    Candy6,
    Selected,
};

class Tile {
    int x = 0, y = 0;
    int w = 70, h = 70;
public:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    int mark = 0;
    SDL_Rect Tile_rect = { x, y, w, h };
    Tile_Status status = Tile_Status::Empty;
    Tile() {};
    ~Tile() {}; 
    void render();
    void render_selected();
    void render_empty();
    void swapTile(Tile otherTile, SDL_Texture* MoveText = NULL, int speed = 20);
};
#endif 