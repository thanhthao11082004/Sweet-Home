 #include "SDL_ttf_function.h"
using namespace std;

// TTF_Font* Font = NULL;
// SDL_Surface* textSurface = NULL;
// SDL_Texture* StrTexture = NULL;

// void LoadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect)
// {
// 	if (TTF_Init() == -1)
// 	{
// 		cerr << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
// 	}
// 	else
// 	{
// 		Font = TTF_OpenFont("font/Southern.ttf", 64);
// 		SDL_Color textColor = { 255, 255, 255, 255 };
// 		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderFillRect(renderer, &Text_rect);
// 		textSurface = TTF_RenderText_Solid(Font, Text, textColor);
// 		StrTexture = SDL_CreateTextureFromSurface(renderer, textSurface);  //
// 		SDL_RenderCopy(renderer, StrTexture, NULL, &Text_rect);
// 		SDL_RenderPresent(renderer);
// 		SDL_FreeSurface(textSurface);
// 	}
// 	TTF_CloseFont(Font);
// 	Font = NULL;
// 	SDL_DestroyTexture(StrTexture);
// 	StrTexture = NULL;
// 	TTF_Quit();
// }

void LoadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect, const char* FontPath, int FontSize, SDL_Color TextColor, SDL_Color BackgroundColor)
{
    if (TTF_Init() == -1)
    {
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
    }
    else
    {
        TTF_Font* Font = TTF_OpenFont(FontPath, FontSize);
        SDL_Surface* textSurface = TTF_RenderText_Solid(Font, Text, TextColor);
        SDL_Texture* StrTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Vẽ màu nền lên vị trí cũ của chữ
        SDL_SetRenderDrawColor(renderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
        SDL_RenderFillRect(renderer, &Text_rect);

        // Vẽ chữ mới
        SDL_RenderCopy(renderer, StrTexture, NULL, &Text_rect);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(StrTexture);
        TTF_CloseFont(Font);
    }
    TTF_Quit();
}






