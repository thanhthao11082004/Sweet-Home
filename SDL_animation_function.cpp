#include "SDL_animation_function.h"

vector<SDL_Texture*> getAnimation(SDL_Renderer* renderer, const char* filePath, int numFrames, int frameWidth, int frameHeight) {
    vector<SDL_Texture*> textures;

    for (int i = 1; i <= numFrames; i++) {
        string fileName = filePath + to_string(i) + ".png";

        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface) {
            printf("IMG_Load error: %s\n", IMG_GetError());
            continue;
        }

        int imageWidth = surface->w;
        int imageHeight = surface->h;

        SDL_Rect frameRect = { 0, 0, frameWidth, frameHeight };
        SDL_Surface* frameSurface = SDL_CreateRGBSurface(0, frameWidth, frameHeight, 32, 0, 0, 0, 0);
        SDL_BlitSurface(surface, &frameRect, frameSurface, NULL);
        SDL_Texture* frameTexture = SDL_CreateTextureFromSurface(renderer, frameSurface);
        textures.push_back(frameTexture);

        SDL_FreeSurface(frameSurface);
        SDL_FreeSurface(surface);
    }

    return textures;
}

// Hàm hiển thị animation trên màn hình
void showAnimation(SDL_Renderer* renderer, vector<SDL_Texture*> textures, int frameWidth, int frameHeight, int fps) {
    int frameDelay = 1000 / fps;
    int numFrames = textures.size();
    int currentFrame = 0;
    int frameCounter = 0;
    int x = 0, y = 0;

    while (true) {
        // Xóa màn hình trước khi vẽ frame mới
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Vẽ frame hiện tại
        SDL_Rect dstRect = { x, y, frameWidth, frameHeight };
        SDL_RenderCopy(renderer, textures[currentFrame], NULL, &dstRect);

        // Tăng frameCounter và currentFrame để chuyển đến frame tiếp theo
        frameCounter += frameDelay;
        if (frameCounter >= 1000) {
            currentFrame = (currentFrame + 1) % numFrames;
            frameCounter -= 1000;
        }

        // Vẽ lên màn hình
        SDL_RenderPresent(renderer);

        // Kiểm tra sự kiện đóng cửa sổ
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }
    }
}
