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
  
  game_scene->sdl_initialize_window(window, window_title);


  while (!game_scene->quitting())
  {
    // game logic...
    game_scene->game_logic();
  }


  close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Game::close()
{
  SDL_DestroyWindow(window);
  window = nullptr;
  
  // Quit SDL2
  SDL_Quit();

  operating = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
