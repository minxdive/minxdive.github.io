/*
  renderer 의 생성과 이벤트를 처리합니다.
*/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "action.h"
#include "game.h"
#include "scene.h"
#include "assets.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
class Game;
class Scene;

using scene_map = std::map<std::string, std::shared_ptr<Scene>>;

constexpr double fps = 60.0;
constexpr double frame_delay = 1000 / fps;

class Game_engine {
  // 키 입력
  int            action_num = 0;
  bool           is_action = false;
  const uint8_t* current_key_states = SDL_GetKeyboardState(nullptr);
  SDL_Event      event;  // 이벤트
  void input_system();  // input 시스템
  void action_key_system();

  // Screen sizes
  float sw, sh;
  
  // 60 FPS
  uint32_t frame_start = 0;
  uint32_t frame_time = 0;
  
  // Scene
  bool        running;
  scene_map   sce_map;
  std::string current_scene;
  std::shared_ptr<Scene> get_current_scene();
  

  // 렌더러, SDL_ttf
  SDL_Renderer* renderer;
  bool initialize_renderer(SDL_Window*& window);
  bool initialize_ttf();
  bool initialize_image();

  // 메인 루프
  bool is_running();  

  // 게임 로직 동작
  void game_logic();

  void close();
  
  Assets* assets_ptr;  // 에셋

public:
  Game_engine(SDL_Window*& window, Assets*& asset, const int& screen_width, const int& screen_height);
  ~Game_engine();

  void change_scene(const std::string& sce_name, std::shared_ptr<Scene> sce_ptr, bool end_cur_sce = false);
  
  Assets*& handle_assets();
  SDL_Renderer*& get_renderer();

  const float& get_screen_width() const;
  const float& get_screen_height() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////

#endif