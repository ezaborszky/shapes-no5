#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "EntityManager.h"
class Game
{
  public:
  sf::RenderWindow m_window;
  std::shared_ptr<Entity> m_player;
  
  
  EntityManager entityManager;
  Game();
  void run();
  void sRender(sf::RenderWindow &window);
  void spawnPlayer();
};
