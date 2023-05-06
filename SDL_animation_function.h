#ifndef SDL_ANIMATION_FUNCTION_H
#define SDL_ANIMATION_FUNCTION_H
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

vector<SDL_Texture*> getAnimation(SDL_Renderer* renderer, const char* filePath, int numFrames, int frameWidth, int frameHeight) ;
void showAnimation(SDL_Renderer* renderer, vector<SDL_Texture*> textures, int frameWidth, int frameHeight, int fps);

#endif