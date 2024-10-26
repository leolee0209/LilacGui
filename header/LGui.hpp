#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <LRect.hpp>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <LWindow.hpp>

#define INTERACTIVE 1
#define NONINTERACTIVE 0
namespace Limb
{
    class LWindow;

    class Tree
    {
    public:
        virtual void draw(SDL_Renderer *renderer, Point parentP = zero){};
        void addSeed(Tree *);
        std::vector<Tree *> *getSeeds();
        void setSeeds(std::vector<Tree *>);
        bool isInteractive();
        Rect getRect();
        void run();
        ~Tree();

    protected:
        bool ifInteractive = NONINTERACTIVE;
        std::vector<Tree *> seeds;
    };

    class Root : public Tree
    {
    public:
        Root(LWindow* window);
        void draw(Point parentP = zero);
        void updateInteractive();
        std::vector<Tree *>* getInteractive();

    private:
        SDL_Renderer *renderer;
        std::vector<Tree *> interactiveSeeds;
    };

    class Label : public Tree
    {
    public:
        Rect rect;
        Color color;

        Label(Rect rect, Color background);
        Rect getRect();
        void draw(SDL_Renderer *renderer, Point parentP = zero);
    };

    class Button : public Tree
    { // Buttons are just touch sensitive blocks, and aren't visible without other elements.
    public:
        Rect range;
        void (*func)();
        void run();
        Button(Rect range, void (*func)());
        Rect getRect();
        void draw(SDL_Renderer *renderer, Point parentP = zero);

    protected:
        bool ifInteractive = INTERACTIVE;
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
        Rect getRect();
    };
    void generateInteractive(Tree *tree, std::vector<Tree *> *ret);
};
