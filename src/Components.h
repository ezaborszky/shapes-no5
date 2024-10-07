#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Vec2.h"

class CTransform
{
  Vec2 pos = {0.0, 0.0};
  Vec2 speed = {0.0, 0.0};
  int rotation = 0;

  CTransform(Vec2 pos, Vec2 speed, int rotation)
    :pos(pos), speed(speed), rotation(rotation){};
};

class CShape
{
  public:
    sf::CircleShape circle;
    CShape(int radius, int points)
      :circle(radius,points)
    {

    }
};







