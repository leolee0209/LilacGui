#include "LGui.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "LWindow.hpp"
#include <cstdio>
#include <LRect.hpp>

using namespace Limb;
using namespace std;



Limb::Label::Label(Rect rect, Color background)
{
    this->rect = rect;
    this->color = background;
}
Limb::Button::Button(Rect range, void (*func)())
{
    this->range = range;
    this->func = func;
}

// parentP is initialized to {0,0}, but set to parent's position if called by parent.
// so "Draw" should only be called on the top element in a tree.
void Root::draw(Point parentP)
{
    for (const auto &t : seeds)
    {
        t->draw(renderer, parentP);
    }
}

void Button::draw(SDL_Renderer *renderer, Point parentP)
{
    vector<Tree *> *seeds = getSeeds();
    for (const auto &t : *seeds)
    {
        t->draw(renderer, parentP);
    }
}

void Label::draw(SDL_Renderer *renderer, Point parentP)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

    SDL_Rect absR = toAbsSDLRect(rect,parentP);
    if (!SDL_RenderFillRect(renderer, &absR))
    {
        // ERROR_L("Can't fill rect. " + std::string(SDL_GetError()));
    }


    vector<Tree *> *seeds = getSeeds();
    Point absP = {absR.x, absR.y};

    for (const auto &t : *seeds)
    {
        t->draw(renderer, absP);
    }
}

void Tree::addSeed(Tree *kid)
{
    if (kid)
        this->seeds.push_back(kid);
}
void Tree::setSeeds(std::vector<Tree *> newSeeds){
    for (auto &t : seeds)
    {
        delete t;
    }
    seeds = std::vector(newSeeds);
}

vector<Tree *> *Tree::getSeeds()
{
    return &seeds;
}

Root::Root(LWindow* window){
    this->renderer = window->getRenderer();
}

Tree::~Tree()
{
    for (auto &t : seeds)
    {
        delete t;
    }
}

Text::Text(Rect rect, std::string text, Color wordColor, TTF_Font *font)
{
    this->rect = rect;
    this->text = text;
    this->wordColor = wordColor;
    this->font = font;
}
void Text::draw(SDL_Renderer *renderer, Point parentP)
{
    SDL_SetRenderDrawColor(renderer, wordColor.r, wordColor.g, wordColor.b, 255);
    SDL_Rect absR = toAbsSDLRect(rect, parentP);

    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Shaded(font, text.c_str(), toSDLColor(wordColor), toSDLColor(transparent)));
    SDL_RenderCopy(renderer, t, NULL, &absR);
    SDL_DestroyTexture(t);

    vector<Tree *> *seeds = getSeeds();
    Point absP = {absR.x, absR.y};
    for (const auto &t : *seeds)
    {
        t->draw(renderer, absP);
    }
}