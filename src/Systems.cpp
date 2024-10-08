#include "Systems.h"
#include "EntityManager.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>


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
      player->cTransform->speed.x = (player->cInput->left) ? -5 : 0;
      player->cTransform->speed.x = (player->cInput->right) ? 5 : 0;
      player->cTransform->speed.x = (player->cInput->up) ? 5 : 0;
      player->cTransform->speed.x = (player->cInput->down) ? -5 : 0;
    }

void sHandleMotion(EntityVec &vec)
{
  for(auto a : vec)
  {
    a->cTransform->pos = a->cTransform->pos + a->cTransform->speed;
  }
}
