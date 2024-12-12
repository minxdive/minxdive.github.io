#include "scene_menu.h"
#include "scene_play.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

Scene_menu::Scene_menu(Game_engine* game_engine) 
  : Scene(game_engine)
{
  std::print("Scene_menu\n");
  
  
  initialize();
}

Scene_menu::~Scene_menu()
{
  destory_scene();

  std::print("~Scene_menu");
}

void Scene_menu::destory_scene()  // test
{
  // 메뉴 텍스처 삭제
  for (auto& e : entity_manager.get_entities("menu_title")) {
    auto& mt = e->get_component<Font_component>();
    SDL_DestroyTexture(mt.font_texture);
    mt.font_texture = nullptr;
  }
  // 레벨 텍스처 삭제
  for (auto& e : entity_manager.get_entities("level1")) {
    auto& l1 = e->get_component<Font_component>();
    SDL_DestroyTexture(l1.font_texture);
    l1.font_texture = nullptr;
  }
  for (auto& e : entity_manager.get_entities("level2")) {
    auto& l2 = e->get_component<Font_component>();
    SDL_DestroyTexture(l2.font_texture);
    l2.font_texture = nullptr;
  }
  for (auto& e : entity_manager.get_entities("level3")) {
    auto& l3 = e->get_component<Font_component>();
    SDL_DestroyTexture(l3.font_texture);
    l3.font_texture = nullptr;
  }

  for (auto& e : entity_manager.get_entities()) {
    e->destroy();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_menu::initialize()
{
  // 액션 등록
  register_action(SDL_SCANCODE_UP, "UP_ARROW");
  register_action(SDL_SCANCODE_DOWN, "DOWN_ARROW");
  register_action(SDL_SCANCODE_RETURN, "ENTER");

  // Entity_manager 초기화
  entity_manager = Entity_manager();

  title = "SUPER MARIO CLONE";
  menu_strings = {"LEVEL 1", "LEVEL 2", "LEVEL 3"};

  // 타이틀
  auto menu_title = entity_manager.add_entity("menu_title");
  menu_title->add_component<Font_component>(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), title, SDL_Color{0xFF, 0xFF, 0xFF}, sc_engine_ptr->get_renderer(), SDL_Rect{10, 10, 600, 100});
  // 레벨
  auto level1 = entity_manager.add_entity("level1");
  level1->add_component<Font_component>(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), menu_strings[0], SDL_Color{0xFF, 0xFF, 0xFF}, sc_engine_ptr->get_renderer(), SDL_Rect{10, 130, 300, 50});
  auto level2 = entity_manager.add_entity("level2");
  level2->add_component<Font_component>(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), menu_strings[1], SDL_Color{0xFF, 0xFF, 0xFF}, sc_engine_ptr->get_renderer(), SDL_Rect{10, 250, 300, 50});
  auto level3 = entity_manager.add_entity("level3");
  level3->add_component<Font_component>(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), menu_strings[2], SDL_Color{0xFF, 0xFF, 0xFF}, sc_engine_ptr->get_renderer(), SDL_Rect{10, 370, 300, 50});

}

/////////////////////////////////////////////////////////////////////////////////////////////////


void Scene_menu::do_action(const Action& act)
{ 
  do_action_system(act);
}

void Scene_menu::do_action_system(const Action& act)
{
  if (act.get_type() == "START") {
    
    if (act.get_name() == "UP_ARROW") {
      if (selected_menu_index > 0) { selected_menu_index--; }
      else { selected_menu_index = menu_strings.size() - 1; }
    }
    else if (act.get_name() == "DOWN_ARROW") {
      selected_menu_index = (selected_menu_index + 1) % menu_strings.size();
    }
    if (act.get_name() == "ENTER") {
      play_game();
    }
  }
  else if (act.get_type() == "END") {
    
  }
}

void Scene_menu::play_game()
{
  sc_engine_ptr->change_scene("PLAY", std::make_shared<Scene_play>(sc_engine_ptr, selected_menu_index), true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_menu::update()
{
  entity_manager.update();
  render_system();
}

void Scene_menu::render_system()
{
  // 배경
  SDL_SetRenderDrawColor(sc_engine_ptr->get_renderer(), 0x33, 0x3C, 0x57, 0xFF);
  SDL_RenderClear(sc_engine_ptr->get_renderer());

  // 타이틀 텍스트
  for (auto& e : entity_manager.get_entities("menu_title")) {
    auto& mt = e->get_component<Font_component>();
    SDL_RenderCopy(sc_engine_ptr->get_renderer(), mt.font_texture, nullptr, &mt.font_rect);
  }
  // 레벨 텍스트
  for (auto& e : entity_manager.get_entities("level1")) {
    auto& l1 = e->get_component<Font_component>();
    l1.index_color_update(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), sc_engine_ptr->get_renderer(), selected_menu_index, 0);
    SDL_RenderCopy(sc_engine_ptr->get_renderer(), l1.font_texture, nullptr, &l1.font_rect);
  }
  for (auto& e : entity_manager.get_entities("level2")) {
    auto& l2 = e->get_component<Font_component>();
    l2.index_color_update(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), sc_engine_ptr->get_renderer(), selected_menu_index, 1);
    SDL_RenderCopy(sc_engine_ptr->get_renderer(), l2.font_texture, nullptr, &l2.font_rect);
  }
  for (auto& e : entity_manager.get_entities("level3")) {
    auto& l3 = e->get_component<Font_component>();
    l3.index_color_update(sc_engine_ptr->handle_assets()->get_font("MARIO_FONT"), sc_engine_ptr->get_renderer(), selected_menu_index, 2);
    SDL_RenderCopy(sc_engine_ptr->get_renderer(), l3.font_texture, nullptr, &l3.font_rect);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////