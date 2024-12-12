#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <vector>
#include "SDL2/SDL_ttf.h"
#include "scene.h"

class Scene_menu : public Scene {
  std::string              title;
  std::vector<std::string> menu_strings;
  size_t                   selected_menu_index = 0;

  void initialize();
  
  void play_game();
  void destory_scene() override;

protected:
  void do_action_system(const Action& act) override; 
  void render_system()                     override;

public:
  Scene_menu(Game_engine* game_engine = nullptr);
  virtual ~Scene_menu();
  
  
  void update()                     override;
  void do_action(const Action& act) override;

  
};

#endif