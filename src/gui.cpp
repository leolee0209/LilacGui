#include "../header/gui.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <cstdio>

using namespace Gui;
using namespace std;
TTF_Font *Tree::font;

void Gui::InitGui(TTF_Font *f)
{
    Tree::font = f;
}

Gui::Label::Label(Rect rect, Rect wordRect, std::string text, Color background)
{
    this->rect = rect;
    this->wordRect = wordRect;
    this->text = text;
    this->color = background;
}
Gui::Button::Button(Rect range, void (*func)(FileControl *, WindowControl *))
{
    this->range = range;
    this->func = func;
}

// parentP is initialized to {0,0}, but set to parent's position if called by parent.
// so "Draw" should only be called on the top element in a tree.
void Tree::draw(SDL_Renderer *renderer, Point parentP)
{
    for (const auto &t : offspring)
    {
        t->draw(renderer, parentP);
    }
}

void Button::draw(SDL_Renderer *renderer, Point parentP)
{
    vector<Tree *> *offspring = getOffspring();
    for (const auto &t : *offspring)
    {
        t->draw(renderer, parentP);
    }
}

void Label::draw(SDL_Renderer *renderer, Point parentP)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

    SDL_Rect *rectS = toSDLRect(&rect);
    SDL_Rect *wordRectS = toSDLRect(&wordRect);
    if (!SDL_RenderFillRect(renderer, rectS))
    {
        // ERROR_L("Can't fill rect. " + std::string(SDL_GetError()));
    }

    SDL_Color wordColor = {200, 200, 200};
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Shaded(font, text.c_str(), wordColor, toSDLColor(&color)));
    SDL_RenderCopy(renderer, t, NULL, wordRectS);
    SDL_DestroyTexture(t);

    vector<Tree *> *offspring = getOffspring();
    Point pos = {rect.x, rect.y};
    for (const auto &t : *offspring)
    {
        t->draw(renderer, pos);
    }
    free(rectS);
    free(wordRectS);
}

void Tree::addKid(Tree *kid)
{
    if (kid)
        this->offspring.push_back(kid);
}

vector<Tree *> *Tree::getOffspring()
{
    return &offspring;
}

Tree::~Tree()
{
    for (auto &t : offspring)
    {
        delete t;
    }
}

void Gui::CloseGui()
{
    TTF_CloseFont(Tree::font);
}

SDL_Rect *Gui::toSDLRect(Rect *r)
{
    SDL_Rect *ret = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    ret->x = r->x;
    ret->y = r->y;
    ret->h = r->h;
    ret->w = r->w;
    return ret;
}
SDL_Color Gui::toSDLColor(Color *c)
{
    return {c->r, c->b, c->g, c->a};
}

SDL_Window *Gui::createWindow()
{
    // Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }
    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return window;
}
