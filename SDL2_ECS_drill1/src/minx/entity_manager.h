#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

/* 
  Entity manager 는 Factory 패턴을 사용
  Factory 는 특정 Entity의 객체를 만듭니다.
  따라서, Entity의 생성과 파괴 모두를 담당합니다.

  std::vector< std::shared_ptr<Entity> >
  vector 에 shared_ptr 을 사용한 이유는 Entity 를 사용 시 
  복사하기 많아지기 때문이라고 합니다. 
  
  만약 Entity가 1000만, 1억이라면...

  std::map 은 key, value 가 항상 정렬된 순서(오름차순)로 저장됩니다.
  이진 탐색 트리 구조

  반복자 무효화를 해결하기 위하여 안전할때 까지 시간을 지연합니다.
  이에 대기실 같은 역할로 entities_to_add, 다음 프레임 시 업데이트 하기 위하여
  update 를 사용하였습니다.
*/
#include <iostream>
#include <algorithm>  // std::remove_if
#include <string>  // std::string
#include <vector>  // std::vector<type>
#include <memory>  // std::shared_ptr<type>
#include <map>     // std::map<types...>

#include "entity.h"

class Entity;

// Entity 를 저장하지 않고, 포인터를 저장
using entity_vector = std::vector<std::shared_ptr<Entity>>;
using entity_map = std::map<std::string, entity_vector>;

class Entity_manager 
{
public:

  Entity_manager();

  std::shared_ptr<Entity> add_entity(const std::string& tag);

  void update();  // 반복자 무효화 문제 해결, 다음 프레임 시 사용(to_add)

  const entity_vector& get_entities();
  const entity_vector& get_entities(const std::string& tag);

private:

  entity_vector entities;         // 모든 Entity 저장
  entity_vector entities_to_add;  // 반복자 무효화 문제 해결, 대기실 같은 역할
  entity_map    entity_map;       // 태그 저장
  size_t        total_entities = 0;    // 프로그램의 모든 Entity의 수

  void remove_dead_entities(entity_vector& entity_vec);
};


#endif
