#include "game.h"

bool Game::operating = false;

Game::Game()
{
  window = nullptr;
  game_scene = new Game_scene();
}

Game::~Game()
{
  delete game_scene;
  if (window != nullptr)
  {
    close();
    window = nullptr;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////





void Game::start(const char* const& window_title)
{
  if (operating) shutdown("Game::start(): window 는 중복 생성할 수 없습니다.");
  
  initialize(window_title, 1280, 720);


  while (!game_scene->quitting())
  {
    // game logic...
    game_scene->game_logic();
  }


  close();
}








///////////////////////////////////////////////////////////////////////////////////////////////////



void Game::initialize(const char* const& window_title, const int& screen_width, const int& screen_height) 
{
  // SDL2 초기화
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
  {
    shutdown("Game::initialize(), SDL_Init(): SDL2 라이브러리 초기화에 실패했습니다. SDL_ERROR: ", SDL_GetError());
  }

  // Linear filtering 설정 (OpenGL, Direct3D 지원)
  if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
  {
    shutdown("Game::initialize(), SDL_SetHint(): Linear filtering 동작에 실패했습니다. SDL_ERROR: ", SDL_GetError());
  }

  // window 생성
  window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            screen_width, screen_height, SDL_WINDOW_SHOWN);
  if (window == nullptr)
  {
    shutdown("Game::initialize(), SDL_CreateWindow(): window 생성에 실패했습니다. SDL_ERROR: ", SDL_GetError());
  }

  game_scene->sdl_initialize_renderer(window, screen_width, screen_height);
}



void Game::close()
{
  SDL_DestroyWindow(window);
  window = nullptr;
  
  // Quit SDL2
  SDL_Quit();

  operating = true;
}





///////////////////////////////////////////////////////////////////////////////////////////////////




void Game::shutdown(const std::string& error_message)
{
  throw std::runtime_error{error_message};
}
void Game::shutdown(const std::string& error_message, const char* const& get_error)
{
  std::string msg = error_message + get_error;
  throw std::runtime_error{msg};
}
