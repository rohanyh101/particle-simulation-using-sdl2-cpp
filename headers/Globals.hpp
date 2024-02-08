#include <bits/stdc++.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL_mixer.h>

using namespace std;

const int WIDTH = 1536, HEIGHT = 814;

const SDL_Color Black = {0x00, 0x00, 0x00};
const SDL_Color White = {0xff, 0xff, 0xff};
const SDL_Color Yellow = {0xff, 0xff, 0x00};
const SDL_Color Red = {0xff, 0x00, 0x00};
const SDL_Color Cyan = {0x00, 192, 0xff};
const SDL_Color Pink = {0xff, 192, 203};
const SDL_Color Orange = {0xff, 128, 0x00};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect* CurrentClip = NULL;
// TTF_Font* Font = NULL;
// TTF_Font* LittleFont = NULL;

void INIT_SDL2() {
if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
    std::cout << "all subsystems initilized" << std::endl;
}

// SDL_DisplayMode currentDisplayMode;

// if(SDL_GetCurrentDisplayMode(0, &currentDisplayMode) != 0){
//     SDL_Log("Unable to get current display mode: %s", SDL_GetError());
//     SDL_Quit();
//     exit(-1);
// }

// cout << currentDisplayMode.w << " " << currentDisplayMode.h - 50 << "\n";

window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
if(window == NULL){
    std::cout << "Couldn't create window" << SDL_GetError() << std::endl;
} else {
    std::cerr << "window created" << std::endl;
}

renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if(renderer == NULL){
    std::cout << "Could not create renderer" << SDL_GetError() << std::endl;
} else {
    std::cerr << "renderer created" << std::endl;
}

if(window == NULL){
    cout << "could not create window" << endl;
    exit(0);
}
}

void CloseSDL(){
    cout << "Game Over" << endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	CurrentClip = NULL;
	// IMG_Quit();
	// TTF_Quit();
	// Mix_Quit();
	SDL_Quit();
}

void MenuState() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}