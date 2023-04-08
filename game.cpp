
#include <sstream>
#include "SDL_utils.h"
#include <vector>
#include "SDL_image_functions.h"
#include "SDL_mixer_function.h"
#include "SDL_ttf_function.h"
#include "game.h"

using namespace std;

const char* BACKGROUND_IMG= "image/background.png";
const char* BGSELECTLEVEL = "image/selectLevel.png";
const char* GAMEBOARD_IMG = "image/gameboard.png";

const char* PLAYBUTTON = "image/playbutton.png";
const char* PLAYBUTTONDOWN = "image/playbuttondown.png";
const char* EASYBUTTON = "image/easy.png";
const char* EASYBUTTONDOWN= "image/easyDown.png";
const char* MEDIUMBUTTON = "image/medium.png";
const char* MEDIUMBUTTONDOWN = "image/mediumDown.png";
const char* HARDBUTTON = "image/hard.png";
const char* HARDBUTTONDOWN = "image/hardDown.png";
const char* SUPERHARDBUTTON = "image/superhard.png";
const char* SUPERHARDBUTTONDOWN = "image/superhardDown.png";

const char* SOUNDONBUTTON = "image/soundOn.png";
const char* SOUNDOFFBUTTON = "image/soundOff.png";

SDL_Rect back_rect = { 0, 0, 900, 600 };
SDL_Rect urScore = { 120, 117, 120, 30 };
SDL_Rect TarScore = { 120, 290, 120, 30 };
SDL_Rect MoveRect = { 190, 362, 70, 30 };
SDL_Rect MoveNum = { 265, 366, 30, 25};
SDL_Rect play_rect = { 700, 500, 150, 80 };
SDL_Rect Result_rect = { 900 / 2 + 50, 600 / 2 - 20, 200, 60 };
SDL_Rect Title_rect = { 570, 100, 200, 50 };

char* IntTostr(long point)
{
    char* score = new char[7];
    stringstream ss;
    ss << point;
    string str = ss.str();
    int n = str.length();
    for (int i = 0; i < 6; i++)
    {
        if (i < 6 - n) score[i] = '0';
        else score[i] = str[i + n - 6];
    }
    score[6] = '\0';
    return score;
}
char* moveStr(int moves)
{
    char* score = new char[6];
    stringstream ss;
    ss << moves;
    string str = ss.str();
    int n = str.length();
    for (int i = 0; i < 2; i++)
    {
        if (i < 2 - n) score[i] = '0';
        else score[i] = str[i + n - 2];
    }
    score[2] = '\0';
    return score;
}

void Button::create_text(const char* up, const char* down) {
    SDL_Surface* image = NULL;
    image = IMG_Load(up);
    Up_text = SDL_CreateTextureFromSurface(renderer, image);
    image = IMG_Load(down);
    Down_text = SDL_CreateTextureFromSurface(renderer, image);
}
void Button::render() {
    if (Up_text == NULL || Down_text == NULL) cout << "loi load" << SDL_GetError() << endl;
    if (status == Button_Status::Up) SDL_RenderCopy(renderer, Up_text, NULL, &Button_rect);
    else SDL_RenderCopy(renderer, Down_text, NULL, &Button_rect);
}

int Game::result(bool res) 
{
    game_button[0].create_text("image/playAgain.png", "image/playAgainDown.png");
    game_button[1].create_text("image/menu.png", "image/menuDown.png");
    game_button[2].create_text("image/quit.png", "image/quitDown.png");
    
    Show_image(renderer, BGSELECTLEVEL, back_rect);
    for (int i = 0; i < 3; i++) {
        game_button[i].render();
    }
    game_button[4].render();
    if (res) LoadFont("You Win!!!", renderer, Title_rect);
    else LoadFont("You Lose!!!", renderer, Title_rect);
    SDL_RenderPresent(renderer);
    while (true) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            if (!Mix_Paused(-1)) Mix_PlayChannel(-1, reverse_sound, 0);
            for (int i = 0; i < 5; i++) {
                if (e.button.x <= game_button[i].Button_rect.x + game_button[i].Button_rect.w
                    && e.button.x >= game_button[i].Button_rect.x
                    && e.button.y <= game_button[i].Button_rect.y + game_button[i].Button_rect.h
                    && e.button.y >= game_button[i].Button_rect.y) {
                    if (game_button[i].status == Button_Status::Up) game_button[i].status = Button_Status::Down;
                    else game_button[i].status = Button_Status::Up;
                    game_button[i].render();
                    SDL_RenderPresent(renderer);
                    SDL_Delay(50);
                    if (i == 4) {
                        if (game_button[i].status == Button_Status::Up) {
                            Mix_ResumeMusic();
                            Mix_Resume(-1);
                        }
                        else {
                            Mix_PauseMusic();
                            Mix_Pause(-1);
                        }
                    }
                    else {
                        game_button[i].status = Button_Status::Up;
                        if (i == 2) return -1;
                        else return i;
                    }
                    SDL_Quit();
                }
            }
        }
    }
}
void Game::initialize_Game() {
    if (!LoadMusic()) cerr << "Failed to load music!" << endl;
    Mix_VolumeChunk(eatable_sound, 32);
    Mix_VolumeChunk(selected_sound, 64);
    Mix_VolumeChunk(reverse_sound, 32);
    Mix_VolumeMusic(16);
    Show_image(renderer, BACKGROUND_IMG, back_rect);
    Show_image(renderer, PLAYBUTTON, play_rect);
    Mix_PlayMusic(background_music, -1);

    game_button[4].Button_rect = { 840, 540, 55, 55 };
    game_button[4].renderer = renderer;
    for (int i = 0; i < 4; i++) {
        game_button[i].Button_rect = { 600, 190 + i * 80, 150, 50 };
        game_button[i].renderer = renderer;
    }
    game_button[0].create_text(EASYBUTTON, EASYBUTTONDOWN);
    game_button[1].create_text(MEDIUMBUTTON, MEDIUMBUTTONDOWN);
    game_button[2].create_text(HARDBUTTON, HARDBUTTONDOWN);
    game_button[3].create_text(SUPERHARDBUTTON, SUPERHARDBUTTONDOWN);
    game_button[4].create_text(SOUNDONBUTTON, SOUNDOFFBUTTON);
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            bool playBut = (e.button.x <= 850) && (e.button.x >= 700) && (e.button.y <= 580) && (e.button.y >= 500);
            if (playBut) {
                if(!Mix_Paused(-1)) Mix_PlayChannel(-1, reverse_sound, 0);
                Show_image(renderer, PLAYBUTTONDOWN, play_rect);
                SDL_Delay(50);
                quit = true;
            }
        }

    }
}
void Game::selectLevel() {
    bool quit = false;
    Show_image(renderer, BGSELECTLEVEL, back_rect);
    for (int i = 0; i < 5; i++) {
        game_button[i].render();
    }
    LoadFont("Select Level", renderer, Title_rect);
    SDL_RenderPresent(renderer);
    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            if (!Mix_Paused(-1))Mix_PlayChannel(-1, reverse_sound, 0);
            for (int i = 0; i < 5; i++) {
                if (e.button.x <= game_button[i].Button_rect.x + game_button[i].Button_rect.w
                    && e.button.x >= game_button[i].Button_rect.x
                    && e.button.y <= game_button[i].Button_rect.y + game_button[i].Button_rect.h
                    && e.button.y >= game_button[i].Button_rect.y) {
                    if (game_button[i].status == Button_Status::Up) game_button[i].status = Button_Status::Down;
                    else game_button[i].status = Button_Status::Up;
                    game_button[i].render();
                    SDL_RenderPresent(renderer);
                    switch (i) {
                    case 0:
                        move = 15;
                        target_point = 10000;
                        quit = true;
                        break;
                    case 1:
                        move = 15;
                        target_point = 30000;
                        quit = true;
                        break;
                    case 2:
                        move = 10;
                        target_point = 50000;
                        quit = true;
                        break;
                    case 3:
                        move = 5;
                        target_point = 100000;
                        quit = true;
                        break;
                    }
                    if (i == 4) {
                        if (game_button[i].status == Button_Status::Up) {
                            Mix_ResumeMusic();
                            Mix_Resume(-1);
                        }
                        else {
                            Mix_PauseMusic();
                            Mix_Pause(-1);
                        }
                    }
                    else game_button[i].status = Button_Status::Up;
                    SDL_Delay(50);
                    break;
                }
            }
        }
    }
}
int Game::Gameplay() {
    Board game_board(renderer);
    long point = 0;
    int moveHid = move;
    Show_image(renderer, GAMEBOARD_IMG, back_rect);
    LoadFont("000000", renderer, urScore);
    LoadFont(IntTostr(target_point), renderer, TarScore);
    LoadFont("Moves:", renderer, MoveRect);
    SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
    SDL_RenderFillRect(renderer, &MoveNum);
    LoadFont(moveStr(moveHid), renderer, MoveNum);
    game_board.Fill_board();
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            if (!game_board.Check_Possible_Move()) {
                SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
                SDL_RenderFillRect(renderer, &urScore);
                LoadFont("No Possible move!", renderer, urScore);
                SDL_Delay(300);
                SDL_RenderFillRect(renderer, &urScore);
                LoadFont("Mix Tiles!", renderer, urScore);
                game_board.Mix_Tiles();
                game_board.render_board();
            }
            game_board.Find_Tile_Selected(e.button.x, e.button.y, moveHid);
            while (game_board.Find_Match(point)) {
                SDL_RenderFillRect(renderer, &MoveNum);
                LoadFont(moveStr(moveHid), renderer, MoveNum);

                game_board.Drop_Tiles(point);

                SDL_RenderFillRect(renderer, &urScore);
                LoadFont(IntTostr(point), renderer, urScore);
            }
            if (point >= target_point) {
                return result(true);
            }
            else if (moveHid == 0) {
                return result(false);
            }
        }
    }
}