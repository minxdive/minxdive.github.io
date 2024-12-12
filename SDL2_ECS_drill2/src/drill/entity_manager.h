#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <map>
#include <memory>
#include <string>
#include "entity.h"

class Entity;

using entity_vec = std::vector<std::shared_ptr<Entity>>;

class Entity_manager {
  entity_vec                        entities;            // 모든 Entity 들(Entities)
  entity_vec                        entities_to_add;     // Entities 는 다음 업데이트에 더합니다.
  std::map<std::string, entity_vec> entity_map;          // map 은 Entity tag 에서 vector
  size_t                            total_entities = 0;  // 생성된 모든 Entities

  void remove_dead_entities(entity_vec& vec);  // 반복되는 코드(반복자 무효화 문제)를 피하는걸 도와주는 함수
public:
  Entity_manager();
  
  void update();
  std::shared_ptr<Entity> add_entity(const std::string& tag);
  const entity_vec& get_entities();
  const entity_vec& get_entities(const std::string& tag);
};

#endif