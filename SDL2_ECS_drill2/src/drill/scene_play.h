#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H

#include "scene.h"

class Scene_play : public Scene {
  size_t level = 0;
  void destory_scene() override;
  bool line_drawing = false;

  std::shared_ptr<Entity> mario;

  void initialize();

  Vector2 grid_to_pixel(const float& grid_x, const float& grid_y);
  const float tile_width = 32;
  const float tile_height = 32;
  
  void spawn_player();
  void spawn_object();

  void movement_system();
  void collision_system();

protected:
  void do_action_system(const Action& act) override;
  void render_system() override;

public:
  Scene_play(Game_engine* game_engine, size_t lev);
  virtual ~Scene_play();

  void do_action(const Action& act) override;
  void update() override;
  
  
};

#endif