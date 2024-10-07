#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include "Entity.h"

void userInput(sf::Window &window, std::shared_ptr<Entity> player, sf::Event& event);
void spawnPlayer(std::shared_ptr<Entity> player); 

