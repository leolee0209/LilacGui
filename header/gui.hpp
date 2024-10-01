#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
class FileControl;
class WindowControl;

namespace Gui
{

    typedef struct Rect
    {
        int x;
        int y;
        int w;
        int h;
    } Rect;

    typedef struct Color
    {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;
    } Color;

    typedef struct Point
    {
        int x;
        int y;
    } Point;
    const Point zero = {0, 0};

    void InitGui(TTF_Font *);
    void CloseGui();
    SDL_Rect *toSDLRect(Rect *r);
    SDL_Color toSDLColor(Color *c);

    class Tree
    {
    public:
        static TTF_Font *font;
        virtual void draw(SDL_Renderer *renderer, Point parentP = zero);
        void addKid(Tree *);
        std::vector<Tree *> *getOffspring();

        ~Tree();

    private:
        std::vector<Tree *> offspring;
    };

    class Label : public Tree
    {
    public:
        Rect rect;
        Rect wordRect;
        Color color;
        std::string text;

        Label(Rect rect, Rect wordRect, std::string text, Color background);
        void draw(SDL_Renderer *renderer, Point parentP = zero);
    };

    class Button : public Tree
    { // Buttons are just touch sensitive blocks, and aren't visible without other elements.
    public:
        Rect range;
        void (*func)(FileControl *, WindowControl *);

        Button(Rect range, void (*func)(FileControl *, WindowControl *));
        void draw(SDL_Renderer *renderer, Point parentP = zero);
    };

    class Text : public Tree
    {
        // TODO
    };
    SDL_Window *createWindow();
};
