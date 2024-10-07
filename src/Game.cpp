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
  m_window.create(sf::VideoMode(1280,768), "Shapes");
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

  int pos = 10;
  sf::Clock deltaClock;
  while(m_window.isOpen())
  {
    sf::Event event;
    entityManager.update();
    ImGui::SFML::ProcessEvent(event);
    
    userInput(m_window, m_player, event);    
    
    
    ImGui::SFML::Update(m_window, deltaClock.restart());
    ImGui::ShowDemoWindow();
    m_window.clear();
    sRender(m_window);
    ImGui::SFML::Render(m_window);
    m_window.display();
  } 
  ImGui::SFML::Shutdown();
}
