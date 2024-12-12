#include "entity.h"

Entity::Entity(const size_t& i, const std::string& ta)
  : id(i), tag(ta) 
{ }

bool Entity::is_active() const { return active; }
size_t Entity::get_id() const { return id; }
const std::string& Entity::get_tag() const { return tag; }
void Entity::destroy() { active = false; }