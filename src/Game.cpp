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
  m_window.create(sf::VideoMode(m_config.wWidth, m_config.wHeight), "Shapes");
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
    sShoot(event, m_player, entityManager, m_window); 
    sHandleMotion(entityManager.getEntitites());

    ImGui::SFML::Update(m_window, deltaClock.restart());
    ImGui::ShowDemoWindow();
   m_window.clear();
    sRender(m_window);
    ImGui::SFML::Render(m_window);
    m_window.display();
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
}


