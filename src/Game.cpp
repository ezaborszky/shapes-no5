#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include "EntityManager.h"
#include "Systems.h"


Game::Game()
{
  m_window.create(sf::VideoMode(m_config.wHeight, m_config.wWidth), "Shapes");
  m_window.setFramerateLimit(60);
  ImGui::SFML::Init(m_window);
}

void Game::sRender(sf::RenderWindow &window)
{
  for(auto a : entityManager.getEntitites())
  {
    window.draw(a->cShape->circle);
  }

}

void Game::run()
{ 
  spawnPlayer();
  int pos = 10;
  sf::Clock deltaClock;
  while(m_window.isOpen())
  {
    
    sf::Event event;
    entityManager.update();
    ImGui::SFML::ProcessEvent(event);

    //INPUT AND MOVEMENT
    userInput(m_window, m_player, event);    
    sMovePlayer(m_player);
    sHandleMotion(entityManager.getEntitites());
    if(event.type == sf::Event::MouseButtonPressed) spawnBullet();

    ImGui::SFML::Update(m_window, deltaClock.restart());
   m_window.clear();
    sRender(m_window);
    ImGui::SFML::Render(m_window);
    entityManager.update();
    m_window.display();
    m_currentFrame++;
  } 
  ImGui::SFML::Shutdown();
}

void Game::spawnPlayer()
{
  m_player = entityManager.addEntity("player");
  m_player->cShape = std::make_shared<CShape>(40, 7);
  m_player->cTransform = std::make_shared<CTransform>(Vec2(20,20), Vec2(5.f,5.f), 0);
  m_player->cInput = std::make_shared<CInput>();
  m_player->cShape->circle.setFillColor(sf::Color(0, 0, 0, 0));
  m_player->cShape->circle.setOutlineThickness(3);
  m_player->cShape->circle.setOutlineColor(sf::Color(255, 0, 0));
  m_player->cShape->circle.setOrigin(m_player->cShape->circle.getRadius(), m_player->cShape->circle.getRadius());
}

void Game::spawnBullet()
{
  if((m_currentFrame - m_lastBullet) > 20)
  {   Vec2 radius = {m_player->cShape->circle.getRadius()/2,m_player->cShape->circle.getRadius()/2};
      Vec2 playLoc = m_player->cTransform->pos;
      sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
      Vec2 mousePosVec = {(float)mousePos.x, (float)mousePos.y};
      Vec2 shootDir = sDirection(playLoc, mousePosVec);
      auto bullet = entityManager.addEntity("bullet");
      bullet->cShape = std::make_shared<CShape>(10,20);
      playLoc = {playLoc.x -5, playLoc.y -5}; 
      bullet->cTransform = std::make_shared<CTransform>(playLoc, shootDir, 0);
      std::cout << "Normal vector X: " << shootDir.x << " Y: " << shootDir.y << std::endl;
      m_lastBullet = m_currentFrame;
  }
}
