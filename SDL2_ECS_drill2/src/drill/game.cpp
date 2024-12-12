#include "game.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game() 
{
  std::print("Game");
  window     = nullptr;
  assets_ptr = nullptr;
  engine_ptr = nullptr;
}

Game::~Game() 
{
  delete engine_ptr;
  delete assets_ptr;
  engine_ptr = nullptr;
  assets_ptr = nullptr;
  shutdown_window();
  std::print("~Game");
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Game::start()
{
  if (initialize_window()) {
    assets_ptr = new Assets();
    engine_ptr = new Game_engine(window, assets_ptr, screen_width, screen_height);
  }
  else {
    shutdown_window();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

bool Game::initialize_window()
{
  // SDL 초기화
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::print("SDL2 초기화에 실패했습니다.\n SDL_Error: {0}", SDL_GetError());
    return false;
	} 
  // Window 생성
  window = SDL_CreateWindow("SDL2 ECS 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::print("window 생성에 실패했습니다.\n SDL_Error: {0}", SDL_GetError());
    return false;
  }
  return true;
}

void Game::shutdown_window()
{
  SDL_DestroyWindow(window);
  window = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}