#include "game_engine.h"
#include "scene_menu.h"
#include "scene_play.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

Game_engine::Game_engine(SDL_Window*& window, Assets*& asset, const int& screen_width, const int& screen_height) 
  : assets_ptr(asset)
{
  std::print("Game_engine");
  renderer = nullptr;
  
  if (initialize_renderer(window) && initialize_ttf() && initialize_image()) {
    sw = static_cast<float>(screen_width);
    sh = static_cast<float>(screen_height);

    change_scene("MENU", std::make_shared<Scene_menu>(this));

    game_logic();
  }
  else {
    close();
  }
}
Game_engine::~Game_engine()
{
  close();
  std::print("\n~Game_engine");
}

void Game_engine::close() 
{
  current_key_states = nullptr;
  
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  assets_ptr = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool Game_engine::initialize_renderer(SDL_Window*& window)
{
  // Renderer 생성
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    std::print("renderer 생성에 실패했습니다.\n SDL_Error: {0}", SDL_GetError());
    return false;
  }
  // Renderer 의 컬러를 설정
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  running = true;

  return true;
}

bool Game_engine::initialize_ttf()
{
  if (TTF_Init() < 0) {  // SDL_ttf 초기화
    std::print("SDL_ttf 초기화에 실패했습니다. SDL_ttf_Error: {0}\n", TTF_GetError());
    return false;
  }
  return true;
}

bool Game_engine::initialize_image()
{
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::print("SDL_image 초기화에 실패했습니다. SDL_image_Error: {0}\n", IMG_GetError());
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool Game_engine::is_running() { return running; }

/////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Renderer*& Game_engine::get_renderer() { return renderer; }
const float& Game_engine::get_screen_width() const { return sw; }
const float& Game_engine::get_screen_height() const { return sh; }

/////////////////////////////////////////////////////////////////////////////////////////////////

void Game_engine::game_logic()
{
  while (is_running()) {
    // Set 60 FPS
    frame_start = SDL_GetTicks();

    // input Logics..
    input_system();
    action_key_system();

/*
    // 배경 그리기, get_current_scene()->update() 으로
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
*/  

    // 해당하는 Scene 업데이트
    get_current_scene()->update();


    SDL_RenderPresent(renderer);

    // Set 60 FPS
    frame_time = frame_start - SDL_GetTicks();
    if (frame_time < frame_delay) SDL_Delay(static_cast<uint32_t>(frame_delay) - frame_time);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Scene> Game_engine::get_current_scene()
{
  return sce_map[current_scene];
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Game_engine::input_system()
{
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN: {
      action_num = event.key.keysym.scancode;
      
      // 메뉴조작 화살표 위아래, 엔터(리턴)
      if (action_num == SDL_SCANCODE_UP || action_num == SDL_SCANCODE_DOWN || action_num == SDL_SCANCODE_RETURN) {  
        if (get_current_scene()->get_action_map().find(event.key.keysym.scancode) == get_current_scene()->get_action_map().end()) {
          //continue;  // 찾는 액션이 없다면 continue
          break;
        }
        //const std::string action_type = (event.key.keysym.scancode) ? "START" : "END";
        const std::string action_type = "START";
        // 액션 전송
        get_current_scene()->do_action(Action(get_current_scene()->get_action_map().at(event.key.keysym.scancode), action_type));
        //continue;
        break;
      }

      is_action = true;
      break;
    }
    case SDL_KEYUP: {
  
      action_num = event.key.keysym.scancode;
      if (action_num == SDL_SCANCODE_UP || action_num == SDL_SCANCODE_DOWN || action_num == SDL_SCANCODE_RETURN) {  
        if (get_current_scene()->get_action_map().find(event.key.keysym.scancode) == get_current_scene()->get_action_map().end()) {
          //continue;  // 찾는 액션이 없다면 continue
          break;
        }
        //const std::string action_type = (event.key.keysym.scancode) ? "START" : "END";
        const std::string action_type = "END";
        // 액션 전송
        get_current_scene()->do_action(Action(get_current_scene()->get_action_map().at(event.key.keysym.scancode), action_type));
        //continue;
        break;
      }
 
      
      is_action = false;
      break;
    }
    }
/*
    // 일부 동작만 이것을 사용
    if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)) {
      // 액션 조회
      if (get_current_scene()->get_action_map().find(event.key.keysym.scancode) == get_current_scene()->get_action_map().end()) {
        continue;  // 찾는 액션이 없다면 continue
      }
      const std::string action_type = (event.key.keysym.scancode) ? "START" : "END";
      // 액션 전송
      get_current_scene()->do_action(Action(get_current_scene()->get_action_map().at(event.key.keysym.scancode), action_type));
    }
*/
  }
}

void Game_engine::action_key_system()
{
  if (is_action || !is_action) {
    // 액션 조회
    if (get_current_scene()->get_action_map().find(action_num) == get_current_scene()->get_action_map().end()) {
      return;  // 찾는 액션이 없다면 return
    }
    const std::string action_type = (is_action) ? "START" : "END";
    // 액션 전송
    get_current_scene()->do_action(Action(get_current_scene()->get_action_map().at(action_num), action_type));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Game_engine::change_scene(const std::string& sce_name, std::shared_ptr<Scene> sce_ptr, bool end_cur_sce)
{
  if (end_cur_sce) get_current_scene()->destory_scene();
  current_scene = sce_name;
  sce_map[sce_name] = sce_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

Assets*& Game_engine::handle_assets()
{
  return assets_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////