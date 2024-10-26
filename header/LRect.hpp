#pragma once
#include <cstdint>
#include <SDL2/SDL.h>
namespace Limb{
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
    const Color transparent = {0, 0, 0, 0};
    SDL_Rect toSDLRect(Rect r);
    SDL_Color toSDLColor(const Color c);
    SDL_Rect toAbsSDLRect(Rect r, Point parent);
    Point toAbsPoint(Point p, Point parent);
    bool withinRect(Point p, Rect r);
}