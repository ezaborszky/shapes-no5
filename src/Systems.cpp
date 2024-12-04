#include "Systems.h"
#include "Components.h"
#include "EntityManager.h"
#include "Vec2.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <memory>
#include "Utility.h"
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
    
   int speedMulti = (a->tag() == "bullet") ? 10 : 1; 

    if(a->tag() == "enemy")
    {
      Vec2 futureLocation = a->cTransform->pos + a->cTransform->speed;
      a->cShape->circle.setRotation(a->cShape->circle.getRotation() + 1);
      if(a->cShape->circle.getRotation() == 360) a->cShape->circle.setRotation(0);
      float reflection = randomNumber(10, 19) / 10.0;
      float reflection2 = -1 * (2.0 - reflection);
      reflection *= -1;
      if(futureLocation.x >= 1024 || futureLocation.x <= 0) a->cTransform->speed.x *= -1;
      if(futureLocation.y >= 768 || futureLocation.y <= 0) a->cTransform->speed.y *= -1;
    }
    
    a->cTransform->pos = a->cTransform->pos + a->cTransform->speed * speedMulti ;

    a->cShape->circle.setPosition(a->cTransform->pos.getVec2f());

  }
}

Vec2 sDirection(Vec2 start, Vec2 target)
{
  //std::cout << "Start X: " << start.x << " Y : " << start.y << std::endl;
  //std::cout << "Mouse X: " << target.x << " Y : " << target.y << std::endl;
  Vec2 difVec = target - start;
  //std::cout << "Difference X: " << difVec.x << " Y: " << difVec.y << std::endl;
  float length = sqrt((difVec.x * difVec.x) + (difVec.y * difVec.y));
  //std::cout << "Length: " << length << std::endl;
  Vec2 normalVec = {difVec.x/length, difVec.y/length};

  return normalVec;
}


