#include "Entity.h"
#include <string>

Entity::Entity(const std::string &tag, int id)
  :m_tag(tag)
,m_id(id){}

bool Entity::isActive() const
{
  return m_active;
}

const std::string& Entity::tag() const
{
  return m_tag;
}

void Entity::destroy()
{
  m_active = false;
}

int Entity::id()
{
  return m_id;
}
