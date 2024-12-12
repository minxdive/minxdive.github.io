#include <fstream>
#include <windows.h>
#include "scene_play.h"
#include "scene_menu.h"
#include "physics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

Scene_play::Scene_play(Game_engine* game_engine, size_t lev)
  : Scene(game_engine), level(lev)
{
  std::print("Scene_play");
  
  initialize();
}

Scene_play::~Scene_play()
{
  destory_scene();
  
  std::print("~Scene_play");
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_play::initialize() 
{
  // 액션 등록
  register_action(SDL_SCANCODE_A, "A");  // 완쪽 이동
  register_action(SDL_SCANCODE_D, "D");  // 오른쪽 이동
  register_action(SDL_SCANCODE_RETURN, "ENTER");  // 그리드 그리기
  register_action(SDL_SCANCODE_K, "K");

  // 스프라이트 등록
  sc_engine_ptr->handle_assets()->add_sprite(sc_engine_ptr->get_renderer(), "MARIO", "assets/sprites/mario.png");
  sc_engine_ptr->handle_assets()->add_sprite(sc_engine_ptr->get_renderer(), "OBJECT", "assets/sprites/object.png");

  // Entity_manager 초기화
  entity_manager = Entity_manager();

  spawn_player();
  spawn_object();

}


/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_play::spawn_player()
{
  mario = entity_manager.add_entity("MARIO");
  mario->add_component<Animation_component>(Animation{"MARIO", 6, 16,16, 32,32}, false);
  mario->add_component<Input_component>();
  mario->add_component<Transform_component>(Vector2{grid_to_pixel(2.75f, 2.0f)}, Vector2{0.0f, 0.0f});
  mario->add_component<Bounding_box_component>(Vector2{24.0F,32.0f});
  mario->add_component<Gravity_component>();
  mario->add_component<State_component>("MARIO", "SMALL");
  
  auto& mar = mario->get_component<Animation_component>();
  mar.animation.add_state("IDLE", 1, 0,0);
  mar.animation.add_state("MOVE", 3, 16,0);
  mar.animation.add_state("TURN", 1, 64,0);
  mar.animation.add_state("JUMP", 1, 80,0);
  mar.animation.add_state("DEATH", 1, 96,0);
}

void Scene_play::spawn_object()
{
  std::ifstream stage;
  switch (level) {
  case 0:
    stage.open("1-1.txt");
    break;
  case 1:
    stage.open("1-2.txt");
    break;
  case 2:
    stage.open("1-3.txt");
    break;
  }

  std::string object;
  float pos_x = 0.0f, pos_y = 0.0f;
  while (stage >> object) {
    if (object == "BLOCK") {
      stage >> pos_x;
      stage >> pos_y;
      auto block = entity_manager.add_entity("OBJECT_IDLE");
      block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      block->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});  // test

      auto& b = block->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 16,0);
    }
    else if (object == "?BOX") {
      stage >> pos_x;
      stage >> pos_y;
      auto box = entity_manager.add_entity("OBJECT_ANIM");
      box->add_component<Animation_component>(Animation{"OBJECT", 18, 16,16, 32,32}, false);
      box->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      box->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});
      //box->add_component<State_component>("?BOX");

      auto& b = box->get_component<Animation_component>();
      b.animation.add_state("ANIM", 3, 0,16);
    }
    else if (object == "BRICK") {
      stage >> pos_x;
      stage >> pos_y;
      auto brick = entity_manager.add_entity("OBJECT_IDLE");
      brick->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      brick->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      brick->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});
      //brick->add_component<State_component>("BRICK");

      auto& b = brick->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 32,0);
    }
    else if (object == "BIGBUSHL") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 80,16);
    }
    else if (object == "BIGBUSHML") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 96,16);
    }
    else if (object == "BIGBUSHM") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 112,16);
    }
    else if (object == "BIGBUSHMR") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 128,16);
    }
    else if (object == "BIGBUSHR") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 144,16);
    }
    else if (object == "BIGBUSHO") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 112,0);
    }
    else if (object == "SMALLBUSHL") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 96,32);
    }
    else if (object == "SMALLBUSHM") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 112,32);
    }
    else if (object == "SMALLBUSHR") {
      stage >> pos_x;
      stage >> pos_y;
      auto bush = entity_manager.add_entity("OBJECT_IDLE");
      bush->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      bush->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& b = bush->get_component<Animation_component>();
      b.animation.add_state("IDLE", 1, 128,32);
    }
    else if (object == "VPIPEOL") {
      stage >> pos_x;
      stage >> pos_y;
      auto pipe = entity_manager.add_entity("OBJECT_IDLE");
      pipe->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      pipe->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      pipe->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});

      auto& p = pipe->get_component<Animation_component>();
      p.animation.add_state("IDLE", 1, 0,112);
    }
    else if (object == "VPIPEOR") {
      stage >> pos_x;
      stage >> pos_y;
      auto pipe = entity_manager.add_entity("OBJECT_IDLE");
      pipe->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      pipe->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      pipe->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});

      auto& p = pipe->get_component<Animation_component>();
      p.animation.add_state("IDLE", 1, 16,112);
    }
    else if (object == "VPIPEUL") {
      stage >> pos_x;
      stage >> pos_y;
      auto pipe = entity_manager.add_entity("OBJECT_IDLE");
      pipe->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      pipe->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      pipe->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});

      auto& p = pipe->get_component<Animation_component>();
      p.animation.add_state("IDLE", 1, 0,128);
    }
    else if (object == "VPIPEUR") {
      stage >> pos_x;
      stage >> pos_y;
      auto pipe = entity_manager.add_entity("OBJECT_IDLE");
      pipe->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      pipe->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      pipe->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});

      auto& p = pipe->get_component<Animation_component>();
      p.animation.add_state("IDLE", 1, 16,128);
    }
    else if (object == "FLAGBLOCK") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});
      flag_block->add_component<Bounding_box_component>(Vector2{32.0f,32.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 64,0);
    }
    else if (object == "CASTLEBLOCK") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 160,32);
    }
    else if (object == "CASTLEOIN") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 176,32);
    }
    else if (object == "CASTLEUIN") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 192,32);
    }
    else if (object == "CASTLEWL") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 160,16);
    }
    else if (object == "CASTLEOBM") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 176,0);
    }
    else if (object == "CASTLEUBM") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 176,16);
    }
    else if (object == "CASTLEWR") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 192,16);
    }
    else if (object == "FLAGBALL") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 96,48);
    }
    else if (object == "FLAGPOLE") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 96,64);
    }
    else if (object == "CLOUDOL") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 208,0);
    }
    else if (object == "CLOUDO") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 224,0);
    }
    else if (object == "CLOUDOR") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 240,0);
    }
    else if (object == "CLOUDUL") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 208,16);
    }
    else if (object == "CLOUDU") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 224,16);
    }
    else if (object == "CLOUDUR") {
      stage >> pos_x;
      stage >> pos_y;
      auto flag_block = entity_manager.add_entity("OBJECT_IDLE");
      flag_block->add_component<Animation_component>(Animation{"OBJECT", 6, 16,16, 32,32}, false);
      flag_block->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{0.0f, 0.0f});

      auto& fb = flag_block->get_component<Animation_component>();
      fb.animation.add_state("IDLE", 1, 240,16);
    }
    // 적
    else if (object == "GOOMBA") {
      stage >> pos_x;
      stage >> pos_y;
      auto goomba = entity_manager.add_entity("ENEMY");
      goomba->add_component<Animation_component>(Animation{"OBJECT", 18, 16,16, 32,32}, false);
      goomba->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{-1.6f, 0.0f});
      goomba->add_component<Bounding_box_component>(Vector2{24.0f,32.0f});
      goomba->add_component<Gravity_component>();
      goomba->add_component<State_component>("GOOMBA", "ALIVE");

      auto& gb = goomba->get_component<Animation_component>();
      gb.animation.add_state("MOVE", 2, 0,32);
      gb.animation.add_state("DEATH", 1, 32,32);
    }
    else if (object == "KOOPATROOPA") {
      stage >> pos_x;
      stage >> pos_y;
      auto koopa_troopa = entity_manager.add_entity("ENEMY");
      koopa_troopa->add_component<Animation_component>(Animation{"OBJECT", 18, 16,24, 32,48}, false);
      koopa_troopa->add_component<Transform_component>(Vector2{grid_to_pixel(pos_x, pos_y)}, Vector2{-1.6f, 0.0f});
      koopa_troopa->add_component<Bounding_box_component>(Vector2{24.0f,32.0f});
      koopa_troopa->add_component<Gravity_component>();
      koopa_troopa->add_component<State_component>("KOOPATROOPA", "ALIVE");

      auto& kt = koopa_troopa->get_component<Animation_component>();
      kt.animation.add_state("MOVE", 2, 0,56);
      kt.animation.add_state("DEATH", 1, 64,64);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_play::do_action(const Action& act)
{
  do_action_system(act);
}
void Scene_play::do_action_system(const Action& act)
{
  if (act.get_type() == "START") {
    if (act.get_name() == "A") {
      mario->get_component<Input_component>().left = true;
      mario->get_component<Animation_component>().flip = true;
    }
    if (act.get_name() == "D") {
      mario->get_component<Input_component>().right = true;
      mario->get_component<Animation_component>().flip = false;
    }
    if (act.get_name() == "ENTER") line_drawing = !line_drawing;
    if (act.get_name() == "K") {
      mario->get_component<Input_component>().jumping = true;
      mario->get_component<Input_component>().jump_state = "JUMP";
    }
  }
  else if (act.get_type() == "END") {
    if (act.get_name() == "A") {
      mario->get_component<Input_component>().left = false;
      mario->get_component<Animation_component>().flip = true;
    }
    if (act.get_name() == "D") {
      mario->get_component<Input_component>().right = false;
      mario->get_component<Animation_component>().flip = false;
    }
    if (act.get_name() == "K") {
      mario->get_component<Input_component>().jumping = false;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 Scene_play::grid_to_pixel(const float& grid_x, const float& grid_y)
{
  return Vector2{tile_width * grid_x, sc_engine_ptr->get_screen_height() - ( (grid_y + 1) * tile_height )};
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_play::update()
{
  entity_manager.update();

  collision_system();
  
  movement_system();

  render_system();

  
  // 그리드 그리기
  if (line_drawing) {
    draw_lines(Vector2{0.0f,0.0f}, Vector2{sc_engine_ptr->get_screen_width(), sc_engine_ptr->get_screen_height()});
  }
}

void Scene_play::render_system()
{
  // 배경
  SDL_SetRenderDrawColor(sc_engine_ptr->get_renderer(), 0x41, 0xA6, 0xF6, 0xFF);
  SDL_RenderClear(sc_engine_ptr->get_renderer());

  

  // 오브젝트 그리기
  for (auto& e : entity_manager.get_entities("OBJECT_IDLE")) {
    auto& ani = e->get_component<Animation_component>();
    auto& trans = e->get_component<Transform_component>(); 
    ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "OBJECT", "IDLE", Vector2{trans.position.x, trans.position.y}, false);
  }
  for (auto& e : entity_manager.get_entities("OBJECT_ANIM")) {
    auto& ani = e->get_component<Animation_component>();
    auto& trans = e->get_component<Transform_component>(); 
    ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "OBJECT", "ANIM", Vector2{trans.position.x, trans.position.y}, false);
  }
  // 적
  for (auto& e : entity_manager.get_entities("ENEMY")) {
    auto& ani = e->get_component<Animation_component>();
    auto& trans = e->get_component<Transform_component>(); 
    auto& sta = e->get_component<State_component>();
    if (sta.state == "DEATH" && sta.name != "KOOPATROOPA") {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "OBJECT", "DEATH", Vector2{trans.position.x, trans.position.y}, false);
    }
    else if (sta.state == "DEATH" && sta.name == "KOOPATROOPA") {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "OBJECT", "DEATH", Vector2{trans.position.x, trans.position.y}, false);
    }
    else if (sta.state == "ALIVE" && sta.name != "KOOPATROOPA") {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "OBJECT", "MOVE", Vector2{trans.position.x, trans.position.y}, false);
    }
    else if (sta.state == "ALIVE" && sta.name == "KOOPATROOPA") {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "OBJECT", "MOVE", Vector2{trans.position.x, trans.position.y - 16.0f}, false);
    }
  }

  // 마리오 그리기
  for (auto& e : entity_manager.get_entities("MARIO")) {
    auto& inp = e->get_component<Input_component>();
    auto& ani = e->get_component<Animation_component>();
    auto& trans = e->get_component<Transform_component>();
    auto& sta = e->get_component<State_component>();
    if (sta.state == "DEATH") {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "MARIO", "DEATH", Vector2{trans.position.x, trans.position.y}, false, ani.flip);
    }
    else if (inp.jump_state == "JUMP") {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "MARIO", "JUMP", Vector2{trans.position.x, trans.position.y}, false, ani.flip);
    }
    else if ( (inp.left && trans.velocity.x > 0.0f) || (inp.right && trans.velocity.x < 0.0f) ) {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "MARIO", "TURN", Vector2{trans.position.x, trans.position.y}, false, ani.flip);
    }
    else if (( (inp.left || !inp.left) && trans.velocity.x < 0.0f) || ( (inp.right || !inp.right) && trans.velocity.x > 0.0f)) {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "MARIO", "MOVE", Vector2{trans.position.x, trans.position.y}, true, ani.flip);
    }
    else if ( (!inp.left || !inp.right) && trans.velocity.x == 0.0f ) {
      ani.animation.update(sc_engine_ptr->get_renderer(), sc_engine_ptr->handle_assets(), "MARIO", "IDLE", Vector2{trans.position.x, trans.position.y}, false, ani.flip);
    }
    
  }
}

void Scene_play::movement_system()
{
  for (auto& e : entity_manager.get_entities()) {
    e->get_component<Transform_component>().prev_pos = e->get_component<Transform_component>().position;
  }
  
  for (auto& m : entity_manager.get_entities("MARIO")) {
    auto& mi = m->get_component<Input_component>();
    auto& mt = m->get_component<Transform_component>();
    
    // 속도를 수정할때는 8 16 32.. 같은 4, 8의 배수로 수정합니다.
    // 마리오 이동
    if (mi.left) {
      mt.velocity.x += -0.08f;
      if (mt.velocity.x <= -5.12f) {
        mt.velocity.x = -5.12f;
      }
    }
    else if (!mi.left && mt.velocity.x <= 0.0f) {
      mt.velocity.x += 0.08f;
      if (mt.velocity.x >= 0.0f) {
        mt.velocity.x = 0.0f;
      }
    }

    if (mi.right) {
      mt.velocity.x += 0.08f;
      if (mt.velocity.x >= 5.12f) {
        mt.velocity.x = 5.12f;
      }
    }
    else if (!mi.right && mt.velocity.x >= 0.0f) {
      mt.velocity.x += -0.08f;
      if (mt.velocity.x <= 0.0f) {
        mt.velocity.x = 0.0f;
      }
    }

    
    // 마리오 점프
    if (mi.can_jump && mi.jumping && mt.velocity.y <= 0.0f && mt.velocity.y >= -13.6f) {
      mt.velocity.y -= 3.04f;
      if (mt.velocity.y < -13.6f) {
        mi.can_jump = false;
      }
    }
    
    
    // 마리오 카메라 이동
    if (mt.position.x >= sc_engine_ptr->get_screen_width()/2) {
      mt.position.x = sc_engine_ptr->get_screen_width()/2;
    }
    if (mt.position.x <= 0.0f) {
      mt.position.x = 0.0f;
    }
  }

  // 움직이지 않는 오브젝트 이동
  for (auto& m : entity_manager.get_entities("MARIO")) {
    for (auto& o : entity_manager.get_entities("OBJECT_IDLE")) {
      auto& mt = m->get_component<Transform_component>();
      auto& ot = o->get_component<Transform_component>();
      // 오브젝트 카메라 이동
      if (mt.position.x >= sc_engine_ptr->get_screen_width()/2) {
        ot.position.x -= mt.velocity.x;
      }
      if (mt.position.x <= mt.init_pos.x) {
        ot.position.x -= 0.0f;
      }
    }
  }
  for (auto& m : entity_manager.get_entities("MARIO")) {
    for (auto& o : entity_manager.get_entities("OBJECT_ANIM")) {
      auto& mt = m->get_component<Transform_component>();
      auto& ot = o->get_component<Transform_component>();
      // 오브젝트 카메라 이동
      if (mt.position.x >= sc_engine_ptr->get_screen_width()/2) {
        ot.position.x -= mt.velocity.x;
      }
      if (mt.position.x <= mt.init_pos.x) {
        ot.position.x -= 0.0f;
      }
    }
  }
  // 적 오브젝트 이동
  for (auto& m : entity_manager.get_entities("MARIO")) {
    for (auto& o : entity_manager.get_entities("ENEMY")) {
      auto& mt = m->get_component<Transform_component>();
      auto& ot = o->get_component<Transform_component>();
      
      // 오브젝트 카메라 이동
      if (mt.position.x >= sc_engine_ptr->get_screen_width()/2) {
        ot.position.x -= mt.velocity.x;
      }
      if (mt.position.x <= mt.init_pos.x) {
        ot.position.x -= 0.0f;
      }
    }
  }



  for (auto& e : entity_manager.get_entities()) {
    if (e->get_component<Gravity_component>().has) {
      e->get_component<Transform_component>().velocity.y += e->get_component<Gravity_component>().gravity;
    }
    e->get_component<Transform_component>().position += e->get_component<Transform_component>().velocity;
  }

}

void Scene_play::collision_system()
{
  Physics p;

  for (auto& e : entity_manager.get_entities()) {
    if (e->get_component<Transform_component>().position.x < -tile_width) {
      e->destroy();
    }
  }

  for (auto& m : entity_manager.get_entities()) { 
    for (auto& o : entity_manager.get_entities()) {  
      if (!m->get_component<Bounding_box_component>().has || !o->get_component<Bounding_box_component>().has) continue;

      // 적 끼리 충돌 무시
      if (m->get_component<State_component>().has && o->get_component<State_component>().has && m->get_tag() == "ENEMY" && o->get_tag() == "ENEMY") {
        continue;
      }
      
      if (( abs(m->get_component<Transform_component>().position.x - o->get_component<Transform_component>().position.x) <= m->get_component<Bounding_box_component>().half_size.x + o->get_component<Bounding_box_component>().half_size.x &&
          abs(m->get_component<Transform_component>().position.y - o->get_component<Transform_component>().position.y) <= m->get_component<Bounding_box_component>().half_size.y + o->get_component<Bounding_box_component>().half_size.y )) {
        if (p.get_overlap(m, o).x > 0 && p.get_overlap(m, o).y > 0 && p.get_previous_overlap(m, o).x < 0 && p.get_previous_overlap(m, o).y < 0 && m->get_component<Transform_component>().position.x > o->get_component<Transform_component>().position.x) {
          m->get_component<Transform_component>().position.x += p.get_overlap(m, o).x;
        }
        if (p.get_overlap(m, o).x > 0 && p.get_overlap(m, o).y > 0 && p.get_previous_overlap(m, o).x < 0 && p.get_previous_overlap(m, o).y < 0 && m->get_component<Transform_component>().position.x < o->get_component<Transform_component>().position.x) {
          m->get_component<Transform_component>().position.x -= p.get_overlap(m, o).x;
        }
        if (p.get_previous_overlap(m, o).y > 0 && m->get_component<Transform_component>().position.x > o->get_component<Transform_component>().position.x) {
          m->get_component<Transform_component>().position.x += p.get_overlap(m, o).x;
          
          
          // 적 속도 반전
          if (m->get_component<State_component>().name != "MARIO" && o->get_component<State_component>().state == "ALIVE") {
            o->get_component<Transform_component>().velocity.x *= -1.0f;
          }
        }
        if (p.get_previous_overlap(m, o).y > 0 && m->get_component<Transform_component>().position.x < o->get_component<Transform_component>().position.x) {
          if (o->get_component<State_component>().state != "ALIVE") {  // 적과 오브젝트 충돌 시 밀어내기 방지
            m->get_component<Transform_component>().position.x -= p.get_overlap(m, o).x;
          }
        
          
          // 마리오 죽음
          if (m->get_component<State_component>().has && o->get_component<State_component>().has && m->get_component<State_component>().name == "MARIO" && o->get_component<State_component>().state == "ALIVE") {
            m->remove_component<Input_component>();
            m->remove_component<Bounding_box_component>();
            m->get_component<State_component>().state = "DEATH";
          }
          
          // 적 속도 반전
          if (m->get_component<State_component>().name != "MARIO" && o->get_component<State_component>().state == "ALIVE") {
            o->get_component<Transform_component>().velocity.x *= -1.0f;
          }
        }
        if (p.get_previous_overlap(m, o).x > 0 && m->get_component<Transform_component>().position.y < o->get_component<Transform_component>().position.y) {
          // 바닥 충돌
          m->get_component<Transform_component>().position.y -= p.get_overlap(m, o).y;
          m->get_component<Transform_component>().velocity.y = 0.0f;
          
          

          if (m->get_component<Input_component>().has) {
            m->get_component<Input_component>().jump_state = "NOT_JUMP";
            m->get_component<Input_component>().can_jump = true;
          }

          // 적 죽음
          if (m->get_component<State_component>().has && o->get_component<State_component>().has && m->get_component<State_component>().name == "MARIO" && o->get_component<State_component>().state == "ALIVE") {
            if (o->get_component<State_component>().name == "GOOMBA") {
              o->get_component<State_component>().state = "DEATH";
              o->get_component<Transform_component>().velocity.x = 0.0f;
              o->remove_component<Bounding_box_component>();
            }
            else if (o->get_component<State_component>().name == "KOOPATROOPA" && o->get_component<State_component>().state == "ALIVE") {
              //o->remove_component<Animation_component>();
              o->get_component<State_component>().state = "DEATH";
              o->get_component<Transform_component>().velocity.x = 0.0f;
            }
          }

        }
        if (p.get_previous_overlap(m, o).x > 0 && m->get_component<Transform_component>().position.y > o->get_component<Transform_component>().position.y) {
          if (!m->get_component<State_component>().has) {
            continue;
          }
          // 머리 충돌
          m->get_component<Transform_component>().position.y += p.get_overlap(m, o).y;
          m->get_component<Transform_component>().velocity.y = 0.0f;
        }
      }
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////

void Scene_play::destory_scene()
{
  for (auto& e : entity_manager.get_entities()) {
    e->destroy();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
