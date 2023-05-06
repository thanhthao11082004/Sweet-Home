#ifndef SDL_TTF_FUNCTION_H
#define SDL_TTF_FUNCTION_H
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

void LoadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect, const char* FontPath, int FontSize, SDL_Color TextColor, SDL_Color BackgroundColor);
void CloseFont();
#endif // !SDL_TTF_FUNCTION_H
