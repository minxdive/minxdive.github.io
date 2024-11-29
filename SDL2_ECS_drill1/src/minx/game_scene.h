/*
  게임의 동작을 담당하는 로직
*/

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#define FPS 60
#define FRAME_DELAY 1000 / FPS

#include <iostream>
#include <fstream>
#include <cmath>

#include "SDL2/SDL.h"

#include "entity.h"
#include "entity_manager.h"
#include "vector2.h"
#include "shutdown.h"

struct Player_config
{
  int shape_radius; 
  int collision_radius; 
  float speed;
  int RGB_R;
  int RGB_G;
  int RGB_B; 
  int shape_vertices;
};

struct Enemy_config 
{
  int shape_radius; 
  int collision_radius; 
  int min_speed;
  int max_speed;
  int min_RGB_range;
  int max_RGB_range;
  int min_shape_vertices;
  int max_shape_vertices;
};

struct Bullet_config
{
  int shape_radius; 
  int collision_radius; 
  float speed;
  int RGB_R;
  int RGB_G;
  int RGB_B; 
  int shape_vertices;
  int lifespan;
};

class Game_scene 
{
public:

  Game_scene();
  ~Game_scene();

  void sdl_initialize_window(SDL_Window* window, const char* const& window_title);  // SDL2 초기화 및 window 생성
  void sdl_initialize_renderer(SDL_Window* window);
  bool quitting();
  void game_logic();  // ECS 의 System 을 동작합니다.
private:  
  Uint32 frame_start;  // FPS
  Uint32 frame_time;
  int screen_width;  // window 크기
  int screen_height;
  float px;  // 플레이어 위치
  float py;
  SDL_Renderer* renderer;
  bool quit;                // 메인 루프 플래그
  SDL_Event event;          // 이벤트 핸들러
  const Uint8* current_key_states;
  
  
  
  Entity_manager entities;  // 유지할 Entity vector
  Player_config player_config;
  Enemy_config enemy_config;
  Bullet_config bullet_config;
  int score = 0;
  int current_frame = 0;
  int last_enemy_spawn_time = 0;
  bool paused = false;  // 일시정지
  //bool running;
  std::shared_ptr<Entity> player;

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
  void spawn_special_weapon(std::shared_ptr<Entity> entity, const Vector2& target);



  void init_config();  // config.txt 초기화
  bool check_collision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);  // 두 Entity 의 충돌을 감지하는 함수
  void blackhole(std::shared_ptr<Entity> bullet);
  void handle_event();  // SDL2 이벤트 처리
  void draw_polygon(SDL_Renderer* renderer, Vector2& pos, float& radius, int& sides, float& angle);  // 정다각형을 그리는 함수
};

#endif
