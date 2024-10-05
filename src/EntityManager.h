#pragma once
#include "Entity.h"
#include <memory>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

class EntityManager
{
    EntityVec m_entities; 
    public:

    EntityManager();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    EntityVec getEntitites();
};
