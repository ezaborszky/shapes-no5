#pragma once

#include <SFML/System/Vector2.hpp>
class Vec2
{
  public:
    float x = 0;
    float y = 0;

    Vec2(){};
    Vec2(float xin, float yin);

    bool operator ==(const Vec2& rhs) const;
    Vec2 operator +(const Vec2&rhs) const; 
    Vec2 operator *(const float val) const;
    Vec2 operator -(const Vec2& rhs) const;
    Vec2& scale(float s); 
    float dist(Vec2 v);
    float length();
    bool operator ==(Vec2 v);
    sf::Vector2f getVec2f();
};

