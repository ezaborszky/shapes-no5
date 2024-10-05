#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "EntityManager.h"
class Game
{
  sf::RenderWindow m_window;

  public:
  
  EntityManager entityManager;
  Game();
  void run();
  void sRender(sf::RenderWindow &window);
};
