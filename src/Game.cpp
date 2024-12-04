#include "Game.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Err.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include "EntityManager.h"
#include "Systems.h"
#include "Utility.h"


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

void Game::setupImGui()
{
    ImGui::Begin("Control Panel");
    for (const auto &entity : entityManager.getEntitites())
    {
        ImVec4 col((entity->cShape->circle.getOutlineColor().r / 255.f), (entity->cShape->circle.getOutlineColor().g / 255.f), (entity->cShape->circle.getOutlineColor().b / 255.f), 1.0f);
        ImGui::TextColored(col, "%zu %.1f %.1f", "asd", entity->cTransform->pos.y, entity->cTransform->pos.x);
    }
    ImGui::End();
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
    sLifeSpan();
    setupImGui();
    spawnEnemy();
    sShoot(event);
    sdetectCol();
    ImGui::SFML::Update(m_window, deltaClock.restart());
   m_window.clear();
    sRender(m_window);
    ImGui::ShowDemoWindow();
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

void Game::spawnEnemy()
{
  if( (m_currentFrame - m_lastEnemy) > 100 )
  {
    auto enemy = entityManager.addEntity("enemy");
    enemy->cShape = std::make_shared<CShape>(22, randomNumber(1, 8));
    int horPos = randomNumber(0,1024);
    int vertPos = randomNumber(0,768);
    int speed1 = randomNumber(0,10);
    int speed2 = randomNumber(0,10);
    if(speed1 <= 5) speed1 *= -1;
    if(speed1 > 5) speed1 = speed1 - 5;
    if(speed2 <= 5) speed1 *= -1;
    if(speed2 > 5) speed2 = speed2 - 5;
    enemy->cTransform = std::make_shared<CTransform>(Vec2(horPos,vertPos), Vec2(speed1,speed2), 11);
    int r,g,b;
    r = randomNumber(0, 255);
    g = randomNumber(0, 255);
    b = randomNumber(0, 255);
    enemy->cShape->circle.setOutlineThickness(3.f);
    enemy->cShape->circle.setOutlineColor(sf::Color(r,g,b));
    enemy->cShape->circle.setFillColor(sf::Color(r,g,b));
        
    m_lastEnemy = m_currentFrame;

  }
}

float Game::distance(Vec2 first, Vec2 last)
{
  float xDif = first.x - last.x;

  float yDif = first.y - last.y;

  float dist = sqrt((xDif*xDif)+(yDif*yDif));

  return dist;

}

void Game::sdetectCol()
{

  for (auto &ent : (entityManager.getEntitites("enemy")) )  {
    for (auto &bul : (entityManager.getEntitites("bullet")))  {
      Vec2 enemyPos = ent->cTransform->pos;
      Vec2 bulletPos = bul->cTransform->pos;

      if(distance(enemyPos,bulletPos) < 55) {
        ent->destroy();
        bul->destroy();
      }
    }
  }

} 

void Game::spawnBullet()
{
  if(m_currentFrame % 10 == 0)
  {   Vec2 radius = {m_player->cShape->circle.getRadius()/2,m_player->cShape->circle.getRadius()/2};
      Vec2 playLoc = m_player->cTransform->pos;
      //sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
      sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);  // Mouse position in window coordinates
      sf::Vector2f worldPos = m_window.mapPixelToCoords(mousePos);  // Convert to world coordinates
      Vec2 mousePosVec = {worldPos.x, worldPos.y};


     // Vec2 mousePosVec = {(float)mousePos.x, (float)mousePos.y};
      Vec2 shootDir = sDirection(playLoc, mousePosVec);
      auto bullet = entityManager.addEntity("bullet");
      bullet->cShape = std::make_shared<CShape>(10,20);
      playLoc = {playLoc.x -5, playLoc.y -5}; 
      bullet->cTransform = std::make_shared<CTransform>(playLoc, shootDir, 0);
      bullet->cLifeSpan = std::make_shared<CLifeSpan>(100);
      //std::cout << "Normal vector X: " << shootDir.x << " Y: " << shootDir.y << std::endl;
      m_lastBullet = m_currentFrame;
  }
}

void Game::sLifeSpan()
{
    for (const auto &a : (entityManager.getEntitites()))
    {
        if (a->cLifeSpan)
        {
            a->cLifeSpan->lifeSpan--;
            if (a->cLifeSpan->lifeSpan <= 0)
            {
                a->destroy();
                return;
            }

            float alphaDecrease = (255.f / a->cLifeSpan->lifeSpan);

            sf::Color currentColor = a->cShape->circle.getFillColor();

            if (alphaDecrease > currentColor.a)
            {
                currentColor.a = 0; // Ensure alpha doesn't go negative
            }
            else
            {
                currentColor.a -= static_cast<sf::Uint8>(alphaDecrease);
            }

            a->cShape->circle.setFillColor(currentColor);

            
            sf::Color currentColorOut = a->cShape->circle.getOutlineColor();

            if (alphaDecrease > currentColorOut.a)
            {
                currentColorOut.a = 0; // Ensure alpha doesn't go negative
            }
            else
            {
                currentColorOut.a -= static_cast<sf::Uint8>(alphaDecrease);
            }

            a->cShape->circle.setOutlineColor(currentColorOut);
        }
    }
}


void Game::sShoot(sf::Event& event)
{
  bool shooting = false;  // Track if the player is shooting

// Inside your event loop
if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
{
    shooting = true;  // Start shooting on initial press
}

// Check for mouse hold in the game loop
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
    if ((m_currentFrame - m_lastBullet) > 1)  // Fire based on your frame interval
    {
        spawnBullet();
    }
}
else
{
    shooting = false;  // Stop shooting when mouse button is released
}

}
