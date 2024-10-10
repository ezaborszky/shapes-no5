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
  unsigned int m_currentFrame = 0;
  unsigned int m_lastBullet = 0;
  unsigned int m_lastEnemy = 0;
  Game();
  void run();
  void sRender(sf::RenderWindow &window);
  void spawnPlayer();
  void spawnBullet();

};



  
