#ifndef ENTITY_H
#define ENTITY_H

/*
  Entity는 unsigned 정수를 id 로 갖습니다.
  또한 string 태그를 사용합니다.
  alive 로 Entity가 살아있는지 확인합니다.

  std::shared_ptr 로 시스템들을 가리킵니다.
*/

#include <string>  // std::string
#include <memory>  // std::shared_ptr<type>

#include "entity_manager.h"
#include "components.h"

class Entity 
{
public:
  // Components shared_ptr
  std::shared_ptr<Transform_component> transform;
  std::shared_ptr<Shape_component> shape;
  std::shared_ptr<Collision_component> collision;
  std::shared_ptr<Input_component> input;
  //std::shared_ptr<Score_component> score;
  std::shared_ptr<Lifespan_component> lifespan;

  // private 멤버 접근 함수
  bool is_active() const;
  const std::string& get_tag() const;
  const size_t get_id() const;
  void destroy();

private:
  friend class Entity_manager;
  
  size_t      id     = 0;          // id
  std::string tag    = "default";  // tag
  bool        active = true;       // entity's check live

  // 생성자, 소멸자
  Entity(const size_t id, const std::string& tag);
};

#endif
