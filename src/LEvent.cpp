#include <LEvent.hpp>
#include <SDL2/SDL.h>
#include <LRect.hpp>

bool Limb::interaction(Root *root)
{
    bool quit = false;
    SDL_Event e;
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {

        switch (e.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            clickEvent(e.button, root);
            break;
        }
    }
    return quit;
}

void Limb::clickEvent(SDL_MouseButtonEvent &e, Limb::Root *root)
{
    if (e.button == SDL_BUTTON_LEFT)
    { // left click
        auto interactives = root->getInteractive();
        Limb::Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);
        for (const auto &i : *interactives)
        {
            if (Limb::withinRect(mouse, i->getRect()))
            {
                i->run();
            }
        }
    }
}