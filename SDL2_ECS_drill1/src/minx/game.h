/*
  SDL2 동작들을 관리합니다.
*/

#ifndef GAME_H
#define GAME_H


#include <stdexcept>  // std::runtime_error
#include <string>  // std::string
#include "SDL2/SDL.h"

#include "game_scene.h"
#include "shutdown.h"

class Game 
{
public:

  Game();
  ~Game();

  void start(const char* const& window_title);
  
private:
  
  Game_scene* game_scene;
  static bool operating;  // window 중복 생성 방지
  
  SDL_Window* window;      // 렌더링 할 window

  void close();                                      // SDL2 종료
};

#endif
