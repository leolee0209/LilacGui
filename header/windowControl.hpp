#pragma once
#include "gui.hpp"
#include <SDL2/SDL.h>

namespace Gui{
    class LWindow{
        public:
            int create();
        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
    };
}
