#include "Systems.h"
#include "Components.h"
#include "EntityManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <iostream>


//USER INPUT -----------------------------------------------------------------------------
void userInput(sf::Window &window, std::shared_ptr<Entity> player, sf::Event& event)
{
  while(window.pollEvent(event))
  {

    //WASD
    //BUTTON DOWN
    switch (event.type)
    {
      case sf::Event::KeyPressed:
        switch (event.key.code) 
        {
          case sf::Keyboard::A:
            player->cInput->left = true;
            break;

          case sf::Keyboard::D:
            player->cInput->right = true;
            break;
          case sf::Keyboard::S:
            player->cInput->down = true;
            break;
          case sf::Keyboard::W:
            player->cInput->up = true;
            break;
        }
        break;
      //BUTTON RELEASE
      case sf::Event::KeyReleased:
        switch (event.key.code)          
        {                                
          case sf::Keyboard::A:          
            player->cInput->left = false; 
            break;                       
                                         
          case sf::Keyboard::D:          
            player->cInput->right = false;
            break;                       
          case sf::Keyboard::S:          
            player->cInput->down = false; 
            break;                       
          case sf::Keyboard::W:          
            player->cInput->up = false;   
            break;                       
        }                                

        break;
//   CLOSE WINDOW
      case sf::Event::Closed:
        window.close();
        break;
    }
  }

  
}

//USER INPUT END -------------------------------------------------------

//PLAYER MOVEMENT

void sMovePlayer(std::shared_ptr<Entity> player)
    {
      player->cTransform->speed.x = (player->cInput->left) ? -5 : (player->cInput->right ? 5 : 0);
      player->cTransform->speed.y = (player->cInput->down) ? 5 : (player->cInput->up ? -5 : 0);
    }

void sHandleMotion(EntityVec &vec)
{
  for(auto& a : vec)
  {
    a->cTransform->pos = a->cTransform->pos + a->cTransform->speed;

    a->cShape->circle.setPosition(a->cTransform->pos.getVec2f());

  }
}

Vec2 sDirection(Vec2 start, Vec2 target)
{
    Vec2 direction = Vec2(target.x - start.x, target.y - start.y);

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    Vec2 finDir;
    finDir.x = direction.x / length;
    finDir.y = direction.y / length;

    return finDir;
}


void sShoot(sf::Event &event, std::shared_ptr<Entity> player, EntityManager& entityManager, sf::Window& window)
{
  if(event.type == sf::Event::MouseButtonPressed)
  {
    Vec2 playLoc = player->cTransform->pos;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    Vec2 mousePosVec = {(float)mousePos.y, (float)mousePos.x};
    Vec2 shootDir = sDirection(playLoc, mousePosVec);
    auto bullet = entityManager.addEntity("bullet");
    bullet->cShape = std::make_shared<CShape>(10,20);
    bullet->cTransform = std::make_shared<CTransform>(playLoc, shootDir, 0);
  }
}
