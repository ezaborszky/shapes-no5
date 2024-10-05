#pragma once
#include <memory>
#include <string>
#include "Components.h"

class Entity
{
  public:
  std::string m_tag = "default";
  Entity(const std::string &tag);
  std::string returnName() const; 
  std::string name;
  std::shared_ptr<CShape> cShape;
};

