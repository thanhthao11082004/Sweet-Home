
#include <sstream>
#include "SDL_utils.h"
#include <vector>
#include "SDL_image_functions.h"
#include "SDL_mixer_function.h"
#include "SDL_ttf_function.h"
#include "game.h"

using namespace std;

// ----------------------ẢNH---------------------

// Background
const char* BACKGROUND_IMG= "image/background.png";
const char* menu = "image/menu.jpg";

const char* setting = "image/setting1.PNG";
const char* play = "image/play1.PNG";

// next

const char* BGSELECTLEVEL = "image/map.png";
const char* OPTIONS = "image/1.png";
const char* SETTINGS = "image/2.png";
const char* GAMEBOARD_IMG = "image/mapp.webp";
const char* bg_score = "image/bg_score.png";

// next -> BGSELECTLEVEL
const char* EASYBUTTON = "image/easy.png";
const char* EASYBUTTONDOWN= "image/easyDown.png";
const char* MEDIUMBUTTON = "image/medium.png";
const char* MEDIUMBUTTONDOWN = "image/mediumDown.png";
const char* HARDBUTTON = "image/hard.png";
const char* HARDBUTTONDOWN = "image/hardDown.png";
const char* SUPERHARDBUTTON = "image/superhard.png";
const char* SUPERHARDBUTTONDOWN = "image/4superhardDown.png";
// âm thanh
const char* SOUNDONBUTTON = "image/soundOn.png";
const char* SOUNDOFFBUTTON = "image/soundOff.png";

// kết quả

const char* LOSE = "image/lose.png";
const char* WIN = "image/win.png";


// ----------------------------Toạ độ------------------

// background



SDL_Rect play1 = { 486 , 461, 335, 108};

SDL_Rect setting1 = {4 , 630, 111/2 + 40 , 95};

// toàn cửa sổ
SDL_Rect back_rect = { 0, 0, 1312 , 737 };

// 
SDL_Rect urScore = { 120, 117, 120, 30 };


SDL_Rect TarScore = { 120, 290, 120, 30 };

// Số bước di chuyển
SDL_Rect MoveRect = { 190, 362, 70, 30 };


SDL_Rect MoveNum = { 265, 366, 30, 25};

// chữ "Select Level"
SDL_Rect Title_rect = { 570, 100, 200, 50 };


// ---------------------------Color-------------------

SDL_Color TextColor = {255,255,255,255};
SDL_Color BackgroundColor = {255,0,255,255};


// Ham chuyen so thanh ky tu 
// ex : 12345 -> 012345
char* IntTostr(long point)
{
    char* score = new char[7];
    stringstream ss;
    ss << point;
    string str = ss.str(); // chuyen so nguyen point thanh chuoi str
    int n = str.length(); // do dai cua chuoi str

    for (int i = 0; i < 6; i++)
    {
        if (i < 6 - n) score[i] = '0';
        else score[i] = str[i + n - 6];
    }

    score[6] = '\0';
    return score;
}


// chuyen so thanh ky tu cho do buoc di chuyen
// ex : 4 -> 04
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



void Button::create_text(const char* up, const char* down) 
{
    SDL_Surface* image = NULL;
    image = IMG_Load(up);
    Up_text = SDL_CreateTextureFromSurface(renderer, image);
    image = IMG_Load(down);
    Down_text = SDL_CreateTextureFromSurface(renderer, image);
}


void Button::render() 
{
    if (Up_text == NULL || Down_text == NULL) 
        cout << "loi load" << SDL_GetError() << endl;

    if (status == Button_Status::Up) 
        SDL_RenderCopy(renderer, Up_text, NULL, &Button_rect);
    else    
        SDL_RenderCopy(renderer, Down_text, NULL, &Button_rect);

}


int Game::result(bool res) 
{
    game_button[0].create_text("image/playAgain.png", "image/playAgainDown.png");
    game_button[1].create_text("image/menu.png", "image/menuDown.png");
    game_button[2].create_text("image/quit.png", "image/quitDown.png");

    if (res)
        Show_image(renderer, WIN, back_rect);
    else 
        Show_image(renderer , LOSE, back_rect);

    for (int i = 0; i < 3; i++) 
        game_button[i].render();
    
    game_button[4].render(); // am thanh
    SDL_RenderPresent(renderer);

    while (true) 
    {
        if (SDL_PollEvent(&e) != 0) 
        {
            if (e.type == SDL_QUIT) 
                SDL_Quit();  // thoát chương trình khi nhận được sự kiện SDL_QUIT

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
            {
                if (!Mix_Paused(-1)) 
                    Mix_PlayChannel(-1, reverse_sound, 0);

                for (int i = 0; i < 5; i++) 
                {
                    if (e.button.x <= game_button[i].Button_rect.x + game_button[i].Button_rect.w
                        && e.button.x >= game_button[i].Button_rect.x
                        && e.button.y <= game_button[i].Button_rect.y + game_button[i].Button_rect.h
                        && e.button.y >= game_button[i].Button_rect.y) 
                    {
                        if (game_button[i].status == Button_Status::Up) 
                            game_button[i].status = Button_Status::Down;
                        else 
                            game_button[i].status = Button_Status::Up;

                        game_button[i].render();
                        SDL_RenderPresent(renderer);
                        SDL_Delay(50);

                        if (i == 4) 
                        {
                            if (game_button[i].status == Button_Status::Up) 
                            {
                                Mix_ResumeMusic();
                                Mix_Resume(-1);
                            }
                            else 
                            {
                                Mix_PauseMusic();
                                Mix_Pause(-1);
                            }   

                        }
                        else 
                        {
                            game_button[i].status = Button_Status::Up;

                            if (i == 2) 
                                return -1;
                            else 
                                return i;
                        }

                        SDL_Quit();
                    }
                }
            }
        }
    }
}

int Game::initialize_Game() 
{

    if (!LoadMusic()) 
        cerr << "Failed to load music!" << endl;

    Mix_PlayMusic(background_music, -1);
    Mix_VolumeChunk(eatable_sound, 50);
    Mix_VolumeChunk(selected_sound, 80);
    Mix_VolumeChunk(reverse_sound, 50);
    Mix_VolumeMusic(100);

    Show_image(renderer, BACKGROUND_IMG, back_rect);
    
    Show_image(renderer, setting , setting1);
    Show_image(renderer, play, play1);

    for (int i = 0; i < 4; i++) 
    {
        game_button[i].Button_rect = { 600, 190 + i * 80, 150, 50 };
        game_button[i].renderer = renderer;
    }

    game_button[4].Button_rect = { 840, 540, 55, 55 };
    game_button[4].renderer = renderer;
    
    game_button[0].create_text(EASYBUTTON, EASYBUTTONDOWN);
    game_button[1].create_text(MEDIUMBUTTON, MEDIUMBUTTONDOWN);
    game_button[2].create_text(HARDBUTTON, HARDBUTTONDOWN);
    game_button[3].create_text(SUPERHARDBUTTON, SUPERHARDBUTTONDOWN);
    game_button[4].create_text(SOUNDONBUTTON, SOUNDOFFBUTTON);


    // code chuc nang cho menu
    bool quit = false;

    while (!quit) 
    {
        if (SDL_PollEvent(&e) != 0 )
        {
            if ( e.type == SDL_QUIT) 
                SDL_Quit();
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
            {
                if ( (e.button.x >= 486) && (e.button.y >= 461) && (e.button.x <= 486 + 335) && (e.button.y <= 461 + 108))
                {
                    return 1 ;
                }
                else if ( (e.button.x >= 4) && (e.button.y >= 630) && (e.button.x<= 4 + 111/2 + 40) && (e.button.y) <= 630 + 95)
                {
                    return 2 ;
                }
            }
        }
    }
}

SDL_Rect settt_rect = { 270, 515, 145, 100};
void Game::selectLevel() 
{
    bool quit = false;

    Show_image(renderer, BGSELECTLEVEL, back_rect);
    // for (int i = 0; i < 5; i++) 
    // {
    //     game_button[i].render();
    // }

    // SDL_RenderPresent(renderer);

    while (!quit) 
    {
        if (SDL_PollEvent(&e) != 0)
        {
            if ( e.type == SDL_QUIT) 
                SDL_Quit(); 
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
            {
                if ( e.button.x >= 270 && e.button.x <= 415 && e.button.y >= 515 && e.button.y <= 615)
                {
                    move = 5 ;
                    target_point = 10000;
                    quit = true;
                }
             }
        }
    }
}

// void LoadFont(const char* Text, SDL_Renderer* renderer, SDL_Rect Text_rect, const char* FontPath, int FontSize, SDL_Color TextColor, SDL_Color BackgroundColor)

int Game::Gameplay() {
    Board game_board(renderer);
    long point = 0;
    int moveHid = move;
    
    Show_image(renderer, GAMEBOARD_IMG, back_rect);
    LoadFont ("000000" ,renderer,urScore);
    LoadFont(IntTostr(target_point), renderer, TarScore);
    LoadFont("Moves:", renderer, MoveRect);
    // SDL_SetRenderDrawColor(renderer, 140, 70, 0, 0);
    SDL_RenderFillRect(renderer, &MoveNum);
    LoadFont(moveStr(moveHid), renderer, MoveNum);
    game_board.Fill_board();
    bool quit = false;
    while (!quit) {
        if ( SDL_PollEvent(&e) != 0 ){

            if ( e.type == SDL_QUIT) SDL_Quit();

            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
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

                TTF_Font* font = TTF_OpenFont("font/Southern.ttf", 64);


                SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "image/bg_score.png");
                SDL_Rect backgroundRect = {urScore.x, urScore.y, urScore.w, urScore.h};
                SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);

                SDL_Rect backgroundRect2 = {MoveNum.x, MoveNum.y, MoveNum.w, MoveNum.h};
                SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect2);



                SDL_RenderFillRect(renderer, &MoveNum);
                CloseFont(font);

                 LoadFont(moveStr(moveHid), renderer, MoveNum);

                game_board.Drop_Tiles(point);

                SDL_RenderFillRect(renderer, &urScore);
                LoadFont(IntTostr(point), renderer, urScore);

                SDL_RenderPresent(renderer);
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
}

const char* esc = "image/esc.PNG";
const char* TURN1 = "image/turn1.jpg";
const char* how_to_play = "image/howToPlay.png";
const char* BACK = "image/back1.png";
const char* NEXT = "image/next.png";

SDL_Rect esc_rect = {880,50,78,75};
SDL_Rect turn1_rect = {560 , 130 , 91, 68};
SDL_Rect turn2_rect = {660 , 130 , 90 , 72};
SDL_Rect next_rect = {510, 520 , 296 , 80};

SDL_Rect how_to_play_rect = {510, 330 , 170 , 35};
SDL_Rect BACK_rect = {355, 60 , 72 , 55};
int x = 0 ;

int Game::Menu()
{
    if ( !Mix_PausedMusic())
    Show_image(renderer, menu, back_rect);
    else 
    Show_image(renderer, TURN1, back_rect);
    bool back = false;
    while ( !back)
    {
        while (SDL_PollEvent(&e) != 0 )
        {
            
            if ( e.type == SDL_QUIT) SDL_Quit();

            else if ( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT )
            {
                // code chuc nag cho phim x
                if ( e.button.x >= 880 && e.button.x <= 958 && e.button.y >= 50 && e.button.y <= 125)
                {
                    return 1 ;
                }
                // code chuc nang cho phim am thanh
                else if (e.button.x >= 560 && e.button.x <= 651 && e.button.y >= 130 && e.button.y <= 198)
                {
                    if ( x % 2 == 1)
                    {
                        Mix_ResumeMusic();
                        Mix_Resume(-1);
                        x++;
                        Show_image ( renderer, menu, back_rect);
                    }
                    else 
                    {
                        Show_image(renderer, TURN1, back_rect);
                        Mix_PauseMusic();
                        Mix_Pause(-1);
                        x++;
                    }
                }
                // code chuc nang cho chu "How to play"
                else if (e.button.x >= 510 && e.button.y >= 330 && e.button.x <= 680 && e.button.y <= 365)
                {
                    if (how_to_play() == 1 ) return 1 ;

                    else continue;
                }
            }   
        }
    }
    return 0 ;
}

int Game::how_to_play()
{
    Show_image (renderer, "image/how_to_play1.jpg" , back_rect); 
    bool quitly = false;
    while ( !quitly)
    {
        while (SDL_PollEvent(&e) != 0 )
        {
            if ( e.type == SDL_QUIT) SDL_Quit();
            else if ( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT )
            {
                if ( e.button.x >= 355 && e.button.y >= 60 && e.button.x <= 427 && e.button.y <= 115)
                {
                    Menu();
                }
                else if ( e.button.x >= 880 && e.button.x <= 958 && e.button.y >= 50 && e.button.y <= 125)
                {
                    return 1 ;
                }
                else if ( e.button.x >= 510 && e.button.y >= 520 && e.button.x <= 806 && e.button.y <= 600)
                {
                    if ( final() == 1 ) return 1;
                    else continue;
                }
            }
        }
    }
}

int Game::final()
{
    Show_image ( renderer, "image/how_to_play_final.jpg" , back_rect);
    bool quitly = false;
    while ( !quitly)
    {
        while (SDL_PollEvent(&e) != 0 )
        {
            if ( e.type == SDL_QUIT) SDL_Quit();
            else if ( e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT )
            {
                if ( e.button.x >= 880 && e.button.x <= 958 && e.button.y >= 50 && e.button.y <= 125)
                {
                    return 1 ;
                }
                else if ( e.button.x >= 355 && e.button.y >= 60 && e.button.x <= 427 && e.button.y <= 115)
                {
                    how_to_play();
                }
                else if ( e.button.x >= 510 && e.button.y >= 520 && e.button.x <= 806 && e.button.y <= 600)
                {
                    Menu();
                }
            }
        }
    }
}