#ifndef SCENE_H
#define SCENE_H

#include "game_engine.h"
#include "entity_manager.h"

class Game_engine;

using action_map = std::map<int, std::string>;

class Scene {
protected:  
  Game_engine*   sc_engine_ptr = nullptr;
  action_map     act_map;
  Entity_manager entity_manager;
  
public:
  Scene();
  Scene(Game_engine* game_engine);
  virtual ~Scene();
  
  void register_action(const int& input_key, const std::string& action_name);
  const action_map& get_action_map() const;
  
  // 순수 가상 함수
  virtual void do_action(const Action& act) = 0;
  virtual void do_action_system(const Action& act) = 0;
  virtual void update() = 0;
  virtual void render_system() = 0;

  // 그리드 그리기
  void draw_lines(const Vector2& p1, const Vector2& p2);

  virtual void destory_scene() = 0;  // test
};

#endif