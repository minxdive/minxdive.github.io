#include "entity_manager.h"

Entity_manager::Entity_manager() 
{

}

std::shared_ptr<Entity> Entity_manager::add_entity(const std::string& tag)
{
  // 새 Entity 객체 생성
  // 모든 Entity를 vector 에 저장
  // tag->entity_vector 의 map 에 저장 (반복자 무효화 때문에 X)
  // 해당하는 Entity 의 shared_ptr 리턴

  // tag, total_entities: Entity(const std::string& tag, size_t id)
  auto entity = std::shared_ptr<Entity>(new Entity(total_entities++, tag));
  entities_to_add.push_back(entity);
  return entity;
}

void Entity_manager::update()
{
  /*
    TODO
    entities_to_add 에서 적절한 위치에 Entity 를 추가합니다.
    모든 Entity 의 vector 에 추가합니다.
    tag 를 key 로 사용하여 map 내부의 vector 에 추가합니다.
  */
  // 각 프레임 시작 시 자동 호출
  // 마지막 프레임에 추가된 Entity 를 이번 프레임에서 사용합니다.
  for (auto e : entities_to_add) 
  {
    entities.push_back(e);
    entity_map[e->get_tag()].push_back(e);
  }
  entities_to_add.clear();
  // 모든 Entity vector 에서 죽은 Entity를 제거합니다.
  remove_dead_entities(entities);

  /*
    Entity map 의 각 vector 에서 죽은 Entity 제거
    map 에서 [key, value] 쌍(pairs)을 반복하는 C++17 방식
  */
  for (auto& [tag, entity_vector] : entity_map) 
  {
    remove_dead_entities(entity_vector);
  }
}



void Entity_manager::remove_dead_entities(entity_vector& entity_vec) 
{
  /*
    TODO
    입력 vector 에서 모든 죽은 entity 를 제거합니다.
    이는 update() 함수에 의해 호출됩니다.
  */
  // 죽은 Entity 만 찾아서 제거
  auto dead = std::remove_if(entity_vec.begin(), entity_vec.end(), [&](std::shared_ptr<Entity> e)
  {
    return e->is_active() == false;
  });
  entity_vec.erase(dead, entity_vec.end());
}

const entity_vector& Entity_manager::get_entities()
{
  return entities;
}

const entity_vector& Entity_manager::get_entities(const std::string& tag)
{
  // TODO: 이것은 잘못된 것입니다. map 에서 올바른 vector 를 반환하세요.
  return entity_map[tag];
}
