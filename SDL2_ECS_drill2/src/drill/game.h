/*
  SDL2 초기화와 window 를 생성합니다.
*/

#ifndef GAME_H
#define GAME_H

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <print>
#include "SDL2/SDL.h"
#include "game_engine.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
class Game_engine;
class Assets;

class Game {
  SDL_Window* window;
  const int   screen_width = 832;
  const int   screen_height = 480;

  Game_engine* engine_ptr;
  Assets*      assets_ptr;
  
  bool initialize_window();
  void shutdown_window();

public:
  Game();
  ~Game();
  void start();
};

/////////////////////////////////////////////////////////////////////////////////////////////////

#endif