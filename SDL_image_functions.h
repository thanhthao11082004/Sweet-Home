#ifndef SDL_IMAGE_FUNCTIONS_H
#define SDL_IMAGE_FUNCTION_H
#include "iostream"
#include <SDL.h>
#include<SDL_image.h>

using namespace std;

void Show_image(SDL_Renderer* renderer, const char* str_image, SDL_Rect rect);
void CreateImg(SDL_Renderer* renderer, const char* str_image, SDL_Rect rect);

#endif