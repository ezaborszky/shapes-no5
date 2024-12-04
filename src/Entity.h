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
  Entity(const std::string &tag, int id);
  
  public:
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CInput> cInput; 
  std::shared_ptr<CLifeSpan> cLifeSpan;
  std::string test = "asd";
  bool isActive() const;
  const std::string &tag() const;
  int id();
  int m_id = 0;
  void destroy();
};

