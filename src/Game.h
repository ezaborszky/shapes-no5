#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "EntityManager.h"

struct ConfigFile
{
  int wHeight = 1024;
  int wWidth = 768;
};

class Game
{
  public:
  sf::RenderWindow m_window;
  std::shared_ptr<Entity> m_player;
  ConfigFile m_config;
  
  EntityManager entityManager;
  Game();
  void run();
  void sRender(sf::RenderWindow &window);
  void spawnPlayer();
};





