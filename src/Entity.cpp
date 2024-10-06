#include "Entity.h"
#include <string>


Entity::Entity(const std::string &tag)
  :m_tag(tag){}

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
