#include <SFML/System/Vector2.hpp>
#include <math.h>
#include "Vec2.h"

Vec2::Vec2(float xin, float yin)
    : x(xin)
    , y(yin)
    {

    }

    Vec2 Vec2::operator + (const Vec2& rhs) const
    {
        return Vec2(x+rhs.x, y+rhs.y);
    }

    Vec2 Vec2::operator * (const float val) const
    {
        return Vec2(x*val, y*val);
    }

    Vec2 Vec2::operator - (const Vec2& rhs) const
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2& Vec2::scale(float s)
    {
        x *= s;
        y *= s;

        return *this;
    }

    float Vec2::dist(Vec2 v)
    {
        float dx = v.x - x;
        float dy = v.y - y;
        return sqrtf((dx*dx) + (dy*dy));
    }

    float Vec2::length()
    {
        return sqrtf((x*x) + (y*y));
    }

    bool Vec2::operator == (Vec2 v)
    {
        return (x == v.x) && (y == v.y);
    }

sf::Vector2f Vec2::getVec2f()
{
 return sf::Vector2f(x,y);
  
}







