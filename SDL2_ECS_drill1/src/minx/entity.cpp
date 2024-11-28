#include "entity.h"

Entity::Entity(const size_t id, const std::string& tag) 
  : id(id), tag(tag) { }

bool Entity::is_active() const
{
  return active;
}

const std::string& Entity::get_tag() const 
{ 
  return tag; 
}

const size_t Entity::get_id() const 
{ 
  return id; 
}

void Entity::destroy() 
{ 
  active = false; 
}
