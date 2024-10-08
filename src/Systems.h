#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <vector>
#include "Entity.h"
#include "EntityManager.h"

void userInput(sf::Window &window, std::shared_ptr<Entity> player, sf::Event& event);
void sMovePlayer(std::shared_ptr<Entity> player); 
void sHandleMotion(EntityVec& vec);
