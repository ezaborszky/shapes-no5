#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class CShape
{
  public:
    sf::CircleShape circle;
    CShape(int radius, int points)
      :circle(radius,points)
    {

    }
};
