#include <iostream>
#include <SDL.h>
#include <ctime>
#include "SDL_utils.h"
#include "game.h"
#include "SDL_image_functions.h"

using namespace std;

const int SCREEN_WIDTH = 1312;
const int SCREEN_HEIGHT = 737;
const char* WINDOW_TITLE = "Sweet Home";
SDL_Rect back_rec = { 0, 0, 1312, 737 };

int start = 1;

int main(int argc, char* argv[])
{
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    srand(time(0));
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    const  Uint32 startTime = SDL_GetTicks();
    SDL_Surface* icon = IMG_Load( "image/icon.png");
    SDL_SetWindowIcon(window , icon);
    SDL_Event e;
    bool quit = false;
    
    while (!quit){

        while (SDL_PollEvent(&e) != 0 ){

            if (e.type == SDL_QUIT) {
                SDL_Quit();
            }

            SDL_RenderClear( renderer );
            SDL_RenderPresent( renderer );

            if ( start == 1)
            {
                while ( SDL_GetTicks() - startTime < 1500)
                {

                // Show_image( renderer , "image/welcome1.jpg" , back_rec);
                // Mở hình ảnh
                SDL_Surface* imageSurface = IMG_Load("image/come1.png");
                SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

                // Hiển thị hình ảnh
                SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
                
                SDL_RenderPresent(renderer);
                // Giải phóng bộ nhớ
                SDL_FreeSurface(imageSurface);
                SDL_DestroyTexture(imageTexture);
                }

                const Uint32 nextTime = SDL_GetTicks();

                while ( SDL_GetTicks() - nextTime < 2000)
                {
                    SDL_Surface* image = IMG_Load( "image/come2.png");
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

                    SDL_RenderCopy(renderer, texture , NULL , NULL);

                    SDL_RenderPresent(renderer);

                    SDL_FreeSurface(image); 
                    SDL_DestroyTexture(texture);           
                }

            }                               
    
            start = 2;

            SDL_RenderClear( renderer );
            SDL_RenderPresent( renderer );
            Game GameH(renderer, e);
            int x = GameH.initialize_Game();   

            // -----------MENU--------------

            if ( x == 1){
                GameH.selectLevel();

                while (!quit){
                    int temp = GameH.Gameplay();

                    if (temp == -1) quit = true;
                    else if (temp == 1) break;
                    else continue;
                } 

            }

            else if ( x == 2)
            {
                if ( GameH.Menu() == 1 ) break;


            }
        }
        
    }

    CloseMusic();
    quitSDL(window, renderer);
    return 0;
}