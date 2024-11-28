/*
  게임의 동작을 담당하는 로직
*/

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#define FPS 60
#define FRAME_DELAY 1000 / FPS

#include <iostream>
#include <cmath>
#include "SDL2/SDL.h"
#include "entity.h"
#include "entity_manager.h"
#include "vector2.h"
/*
struct Player_config
{
  int shape_radius, 
  collision_radius, 
  fill_color_r, fill_color_g, fill_color_b, 
  outline_color_r, outline_color_g, outline_color_b, 
  outline_thickness, 
  shape_vertices;
  float speed;
};

struct Enemy_config 
{
  int shape_radius, 
  collision_radius, 
  outline_color_r, outline_color_g, outline_color_b, 
  outline_thickness, 
  min_vertices, max_vertice, 
  small_lifespan, 
  spawn_interval;
  float min_speed, max_speed; 
};

struct Bullet_config
{
  int shape_radius, 
  collision_radius, 
  fill_color_r, fill_color_g, fill_color_b, 
  outline_color_r, outline_color_g, outline_color_b, 
  outline_thickness, 
  shape_vertices, 
  small_lifespan;
  float speed;
};
*/
class Game_scene {
public:
  //Game_scene(const std::string& config);
  Game_scene();
  ~Game_scene();
  void sdl_initialize_renderer(SDL_Window* window, const int& screen_width, const int& screen_height);
  bool quitting();
  void game_logic();  // ECS 의 System 을 동작합니다.
private:  
  Uint32 frame_start;  // FPS
  Uint32 frame_time;
  
  int sw;  // window 크기
  int sh;
  
  SDL_Renderer* renderer;
  bool quit;                // 메인 루프 플래그
  SDL_Event event;          // 이벤트 핸들러
  const Uint8* current_key_states;
  
  Entity_manager entities;  // 유지할 Entity vector
  
  //Player_config player_config;
  //Enemy_config enemy_config;
  //Bullet_config bullet_config;

  float px;  // 플레이어 위치
  float py;

  int score = 0;
  int current_frame = 0;
  int last_enemy_spawn_time = 0;
  //bool paused = false;
  //bool running;
  
  std::shared_ptr<Entity> player;

  bool check_collision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);  // 두 Entity 의 충돌을 감지하는 함수

  void movement_system();
  void input_system();
  void liftspan_system();
  void render_system();
  void enemy_spawner_system();
  void collision_system();

  void spawn_player();
  void spawn_enemy();
  void spawn_small_enemimes(std::shared_ptr<Entity> entity);
  void spawn_bullet(std::shared_ptr<Entity> entity, const Vector2& target);
  void spawn_special_weapon(std::shared_ptr<Entity> entity);

  void handle_event();  // SDL2 이벤트 처리
  // 정다각형을 그리는 함수
  void draw_polygon(SDL_Renderer* renderer, Vector2& pos, float& radius, int& sides, float& angle);
};

#endif
