#pragma once
#include "LGui.hpp"
#include <SDL2/SDL.h>

namespace Limb
{
    class LWindow
    {
    public:
        bool create();
        bool close();
        void clear();
        void present();
        SDL_Renderer *getRenderer();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
    };
}
