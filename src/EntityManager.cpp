#include "EntityManager.h"
#include <iostream>

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
  auto e = std::shared_ptr<Entity>(new Entity(tag));
  m_entities.push_back(e);
  return e;
} 

EntityVec EntityManager::getEntitites()
{
  return m_entities;
}

EntityManager::EntityManager(){};
