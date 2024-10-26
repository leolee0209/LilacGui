#include "LWindow.hpp"
#include <SDL2/SDL_image.h>
#include <string>
#include <LLog.hpp>
using namespace std;

bool Limb::LWindow::create()
{
    // Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        ERROR("SDL could not initialize! SDL_Error: " + string(SDL_GetError()));
    }

    // Create window
    window = SDL_CreateWindow("ImageViewer",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        ERROR("Window could not be created! SDL_Error: " + string(SDL_GetError()));
    }
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    // screenWidth = DM.w;
    // screenHeight = DM.h;

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        ERROR("Renderer could not be created! SDL_Error: " + string(SDL_GetError()));
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        ERROR("SDL_image could not initialize! SDL_image Error: " + string(IMG_GetError()));
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    // init ttf
    if (TTF_Init() < 0)
    {
        ERROR("SDL_ttf could not initialize! Error: " + string(TTF_GetError()));
    }

    // Set render color to black ( background will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear winow
    SDL_RenderClear(renderer);

    return 0;
}

bool Limb::LWindow::close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    return true;
}

void Limb::LWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
void Limb::LWindow::present()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer *Limb::LWindow::getRenderer()
{
    return renderer;
}
