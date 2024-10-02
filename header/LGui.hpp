#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <LRect.hpp>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <LWindow.hpp>

namespace Limb
{
    class LWindow;

    class Tree
    {
    public:
        virtual void draw(SDL_Renderer *renderer, Point parentP = zero);
        void addSeed(Tree *);
        std::vector<Tree *> *getSeeds();
        void setSeeds(std::vector<Tree *>);
        ~Tree();

    protected:
        std::vector<Tree *> seeds;
    };

    class Root : public Tree
    {
    public:
        Root(LWindow* window);
        void draw(Point parentP = zero);
    private:
        SDL_Renderer *renderer;
    };

    class Label : public Tree
    {
    public:
        Rect rect;
        Color color;

        Label(Rect rect, Color background);
        void draw(SDL_Renderer *renderer, Point parentP = zero);
    };

    class Button : public Tree
    { // Buttons are just touch sensitive blocks, and aren't visible without other elements.
    public:
        Rect range;
        void (*func)();

        Button(Rect range, void (*func)());
        void draw(SDL_Renderer *renderer, Point parentP = zero);
    };

    class Text : public Tree
    {
    public:
        TTF_Font *font;
        Rect rect;
        std::string text;
        Color wordColor;
        Text(Rect rect, std::string text, Color wordColor, TTF_Font *font);
        void draw(SDL_Renderer *renderer, Point parentP = zero);
    };
};
