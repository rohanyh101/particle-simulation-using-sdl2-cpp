#include <bits/stdc++.h>
#include <SDL2/SDL.h>
using namespace std;

#include "./headers/Globals.hpp"

int getRefreshRate(SDL_Window*);
void createParticle();
float getFPS();
void modTitle(SDL_Window*);

enum GameState {
    MENU,
    PLAY,
    PAUSE,
    GAME_OVER
};

GameState gameState = GameState::MENU;

const int PARTICLES = 20;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

Uint32 startTime = 0;
int frameCount = 0;

struct Particle {
    int x, y;
    int velocity;
    int lifetime;
};

std::vector<Particle> particles;

int main(int args, char *argv[]) {

    INIT_SDL2();

    MenuState();
    // std::cerr << "refresh_rate: " << getRefreshRate(window) << std::endl;

    SDL_Event e;

    while(true){
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for(int i = 0; i < PARTICLES; ++i){
            createParticle();
        }

        double gravity = (double) 9.81f;
        double deltaTime = (double) 0.380f;

        for(size_t i = 0; i < particles.size(); ++i){
            Particle &p = particles[i];
            p.velocity = gravity * deltaTime;
            p.y += p.velocity * deltaTime;
            --p.lifetime;

            if(p.lifetime <= 0){
                particles.erase(particles.begin() + i);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, p.lifetime * 2);
                SDL_RenderDrawPoint(renderer, p.x, p.y);
            }
        }

        SDL_RenderPresent(renderer);
        // SDL_Delay(10);

        frameTime = SDL_GetTicks() - frameStart;

        // this ensures that the distence between frames is always 16ms, if not then an delay will be added to cover up the extra delay ...
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

        modTitle(window);
    }

    CloseSDL();
    return EXIT_SUCCESS;
}

void modTitle(SDL_Window* window) {
    int fR = getFPS();
    std::string title = "SMOKE EFFECT     FPS: " + std::to_string(static_cast<int>((fR >= 0) ? fR : 0));
    SDL_SetWindowTitle(window, title.c_str());
}

float getFPS() {
    Uint32 currentTime = SDL_GetTicks();
    static Uint32 prevTime = currentTime;
    ++frameCount;

    if (currentTime - prevTime >= 1000) {
        float fps = frameCount / ((currentTime - prevTime) / 1000.0f);
        prevTime = currentTime;
        frameCount = 0;
        return fps;
    }

    return frameCount / ((currentTime - prevTime) / 1000.0f);
}

void createParticle()
{
    Particle p;
    p.x = (std::rand() % WIDTH);
    p.y = 0;// HEIGHT / 4;
    p.velocity = std::rand() % 5 + 1;
    p.lifetime = std::rand() % 665 + 100;
    particles.push_back(p);
}

int getRefreshRate(SDL_Window *window) {
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}