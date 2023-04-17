#include <iostream>
#include <SDL.h>
#include <ctime>
#include "SDL_utils.h"
#include "game.h"

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Sweet Home";

int main(int argc, char* argv[])
{
   /* SDL_Window* window;
    SDL_Renderer* renderer;
    srand(time(0));
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    //render gameplay
    /*SDL_Event e;
    bool quit = false;
    while ( !quit){
        while (SDL_PollEvent(&e) != 0 ){
        if (e.type == SDL_QUIT) {
            quit = true;
            break;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
    
       quit = true;
       break;
        }
      
       else{
        Game GameH(renderer, e);
        GameH.initialize_Game();
        GameH.selectLevel();
        while (!quit) {
            int temp = GameH.Gameplay();
            if (temp == -1) quit = true;
            else if (temp == 1) break;
            else continue;
        }
}  
        } 

    CloseMusic();
    quitSDL(window, renderer);
    return 0;
}
*/
if (SDL_Init(SDL_INIT_VIDEO) < 0 ){
    cout << "SDL could not initialize! SDL_Error: " << end;
    cout << SDL_Error();
    return 1 ;
}

SDL_Window* window = SDL_CreateWindow("Sweet Home" ,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_)