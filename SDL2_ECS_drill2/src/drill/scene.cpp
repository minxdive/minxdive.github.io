#include "scene.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

Scene::Scene() { } 

Scene::Scene(Game_engine* game_engine) : sc_engine_ptr(game_engine)
{ 
  std::print("Scene");
  game_engine->handle_assets()->add_font("MARIO_FONT", "assets/fonts/super-mario-bros-nes/super-mario-bros-nes.ttf");
}

Scene::~Scene()
{
  entity_manager.update();
  std::print("~Scene");
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::register_action(const int& input_key, const std::string& action_name)
{
  act_map[input_key] = action_name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

const action_map& Scene::get_action_map() const
{
  return act_map;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene::draw_lines(const Vector2& p1, const Vector2& p2)
{
  for (float i = 0.0f; i <= p2.y; i += 32.0f) {
    SDL_SetRenderDrawColor(sc_engine_ptr->get_renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLineF(sc_engine_ptr->get_renderer(), p1.x, i, p2.x, i);
  }
  for (float i = 0.0f; i <= p2.x; i += 32.0f) {
    SDL_SetRenderDrawColor(sc_engine_ptr->get_renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLineF(sc_engine_ptr->get_renderer(), i, p1.y, i, p2.y);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////