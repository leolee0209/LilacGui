#include <LRect.hpp>

using namespace Limb;
SDL_Rect Limb::toSDLRect(Rect r)
{
    return {r.x,r.y,r.h,r.w};
}
SDL_Color Limb::toSDLColor(const Color c)
{
    return {c.r, c.b, c.g, c.a};
}
SDL_Rect Limb::toAbsSDLRect(Rect r,Point parent){
    Point absP = toAbsPoint({r.x, r.y},parent);
    return {absP.x, absP.y, r.h, r.w};
}
Point Limb::toAbsPoint(Point p, Point parent)
{
    return {p.x + parent.x, p.y + parent.y};
}
bool Limb::withinRect(Point p, Rect r){
    return  p.x >= r.x && 
            p.y >= r.y && 
            p.x <= r.x + r.w && 
            p.y <= r.y + r.h;
}
