#pragma once
#include <memory>
#include <string>
#include "Components.h"

class Entity
{
  friend class EntityManager;
  bool m_active = true;
  std::string m_tag = "default";

  //constructor and deconstructor
  Entity(const std::string &tag);
  
  public:
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CInput> cInput; 
  std::shared_ptr<CLifeSpan> cLifeSpan;
  std::string test = "asd";
  bool isActive() const;
  const std::string &tag() const;
  const size_t id() const;
  void destroy();
};

