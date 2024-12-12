#include "entity_manager.h"

Entity_manager::Entity_manager() { }

std::shared_ptr<Entity> Entity_manager::add_entity(const std::string& tag)
{
  auto entity = std::shared_ptr<Entity>(new Entity(total_entities++, tag));
  entities_to_add.push_back(entity);
  return entity;
}

void Entity_manager::update()
{
  for (auto e : entities_to_add) 
  {
    entities.push_back(e);
    entity_map[e->get_tag()].push_back(e);
  }
  entities_to_add.clear();
  remove_dead_entities(entities);
  for (auto& [tag, entity_vector] : entity_map) 
  {
    remove_dead_entities(entity_vector);
  }
}

void Entity_manager::remove_dead_entities(entity_vec& entity_vec) 
{
  auto dead = std::remove_if(entity_vec.begin(), entity_vec.end(), [&](std::shared_ptr<Entity> e)
  {
    return e->is_active() == false;
  });
  entity_vec.erase(dead, entity_vec.end());
}

const entity_vec& Entity_manager::get_entities()
{
  return entities;
}

const entity_vec& Entity_manager::get_entities(const std::string& tag)
{
  return entity_map[tag];
}
