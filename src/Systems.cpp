#include "Systems.h"
#include <SFML/Window/Window.hpp>
#include <iostream>

void userInput(sf::Window &window, std::shared_ptr<Entity> player, sf::Event& event)
{
  while(window.pollEvent(event))
  {
    std::cout << event.key.code << std::endl;
  }

  
}
