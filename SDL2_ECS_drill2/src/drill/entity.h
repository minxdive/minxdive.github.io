#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <tuple>
#include "entity_manager.h"
#include "components.h"

using components_tuple = std::tuple<
  Transform_component, 
  Input_component, 
  Font_component, 
  Animation_component, 
  Bounding_box_component, 
  Gravity_component, 
  State_component
>;

class Entity {
  friend class Entity_manager;

  size_t      id = 0;
  std::string tag = "default";
  bool        active = true;
  components_tuple components;
  Entity(const size_t& i, const std::string& ta);

public:
  bool is_active() const;
  size_t get_id() const;
  const std::string& get_tag() const;
  void destroy();

  template<typename T>
  bool has_component() const 
  {
    return get_component<T>().has;
  }

  template<typename T, typename... T_args>
  T& add_component(T_args&&... args)
  {
    auto& comp = get_component<T>();
    comp = T(std::forward<T_args>(args)...);
    comp.has = true;
    return comp;
  }
  template <typename T>
  T& get_component()
  {
    return std::get<T>(components);
  }
  template<typename T> 
  const T& get_component() const 
  {
    return std::get<T>(components);
  }
  template<typename T>
  void remove_component()
  {
    get_component<T>() = T();
  }
};

#endif