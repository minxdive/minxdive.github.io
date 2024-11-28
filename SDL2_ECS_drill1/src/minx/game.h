/*
  SDL2 동작들을 관리합니다.
*/

#ifndef GAME_H
#define GAME_H


#include <stdexcept>  // std::runtime_error
#include <string>  // std::string
#include "SDL2/SDL.h"

#include "game_scene.h"

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

  

  void initialize(const char* const& window_title, const int& screen_width, const int& screen_height);  // SDL2 초기화 및 window 생성
  
  void close();                                      // SDL2 종료
  
  void shutdown(const std::string& error_message);   // 예외처리
  void shutdown(const std::string& error_message, const char* const& get_error);
};

#endif
