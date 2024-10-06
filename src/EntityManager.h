#pragma once
#include "Entity.h"
#include <map>
#include <memory>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
    EntityVec m_entities; 
    EntityVec m_entitiesToAdd;
    EntityMap m_entityMap;
    public:

    EntityManager();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    void removeDeadEntities(EntityVec& vec);
    void update();
    EntityVec getEntitites();
};
