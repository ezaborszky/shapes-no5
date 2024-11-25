#include "EntityManager.h"
#include <string>

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
  auto e = std::shared_ptr<Entity>(new Entity(tag));
  m_entitiesToAdd.push_back(e);
  return e;
} 

void EntityManager::removeDeadEntities(EntityVec& vec)
{
  auto del = std::remove_if(vec.begin(), vec.end(), [](const std::shared_ptr<Entity>& entity) {return !entity->isActive();});
  vec.erase(del,vec.end());
}

void EntityManager::update()
{
  for(auto e : m_entitiesToAdd)
  {
    m_entities.push_back(e);
    m_entityMap[e->tag()].push_back(e);
  }

  removeDeadEntities(m_entities);

  for(auto &[tag, entites] : m_entityMap) removeDeadEntities(entites);

  m_entitiesToAdd.clear();


}

EntityVec &EntityManager::getEntitites()
{
  return m_entities;
}

EntityVec &EntityManager::getEntitites(const std::string& tag)
{
  return m_entityMap[tag];
}

EntityManager::EntityManager(){};
