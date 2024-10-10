#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <vector>
#include "Entity.h"
#include "EntityManager.h"
#include "Vec2.h"
#include <math.h>

void userInput(sf::Window &window, std::shared_ptr<Entity> player, sf::Event& event);
void sMovePlayer(std::shared_ptr<Entity> player); 
void sHandleMotion(EntityVec& vec);
void sShoot(sf::Event& event, std::shared_ptr<Entity> player, EntityManager& entityManager, sf::Window& window, unsigned int currentFrame, unsigned int& lastFrame); 
Vec2 sDirection(Vec2 start, Vec2 target);
