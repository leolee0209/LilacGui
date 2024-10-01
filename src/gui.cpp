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

