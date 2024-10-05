#include "Entity.h"


Entity::Entity(const std::string &tag)
  :m_tag(tag){}

  std::string Entity::returnName() const 
{
  return m_tag;
}
