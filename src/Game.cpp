#include "Game.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>

Game::Game()
{
  m_window.create(sf::VideoMode(1280,768), "Shapes");
  m_window.setFramerateLimit(60);
  ImGui::SFML::Init(m_window);
}

void Game::run()
{
  sf::Clock deltaClock;
  while(m_window.isOpen())
  {
    sf::Event event;
    while(m_window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      if(event.type == sf::Event::Closed)
      {
        m_window.close();
      }
    }
    
    ImGui::SFML::Update(m_window, deltaClock.restart());
    ImGui::ShowDemoWindow();
    m_window.clear();
    ImGui::SFML::Render(m_window);
    m_window.display();
  } 
  ImGui::SFML::Shutdown();
}
