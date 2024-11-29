#include "game_scene.h"

Game_scene::Game_scene()
{
  renderer = nullptr;
  init_config();
}
Game_scene::~Game_scene()
{
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Game_scene::init_config()
{
  std::ifstream fin("config.txt");
  if (!fin) shutdown("Failed open to config.txt!");
  
  std::string eater;  // 문자열 먹기
  if (fin >> eater)
  {
    fin >> screen_width >> screen_height;  // screen
    fin >> eater;
    fin >> player_config.shape_radius >>  // player
           player_config.collision_radius >> 
           player_config.speed >> 
           player_config.RGB_R >> 
           player_config.RGB_G >> 
           player_config.RGB_B >> 
           player_config.shape_vertices;
    fin >> eater;
    fin >> enemy_config.shape_radius >>  // enemy
           enemy_config.collision_radius >> 
           enemy_config.min_speed >> 
           enemy_config.max_speed >> 
           enemy_config.min_RGB_range >> 
           enemy_config.max_RGB_range >> 
           enemy_config.min_shape_vertices >>
           enemy_config.max_shape_vertices;
    fin >> eater;
    fin >> bullet_config.shape_radius >>  // bullet
           bullet_config.collision_radius >> 
           bullet_config.speed >> 
           bullet_config.RGB_R >> 
           bullet_config.RGB_G >> 
           bullet_config.RGB_B >> 
           bullet_config.shape_vertices >> 
           bullet_config.lifespan;
  }
/*
  std::cout << screen_width << ' ' << screen_height << '\n'
            << player_config.shape_radius << ' ' 
            << player_config.collision_radius << ' ' 
            << player_config.speed << ' ' 
            << player_config.RGB_R << ' ' 
            << player_config.RGB_G << ' ' 
            << player_config.RGB_B << ' ' 
            << player_config.shape_vertices << '\n'
            << enemy_config.shape_radius << ' ' 
            << enemy_config.collision_radius << ' ' 
            << enemy_config.min_speed << ' ' 
            << enemy_config.max_speed << ' ' 
            << enemy_config.min_RGB_range << ' ' 
            << enemy_config.max_RGB_range << ' ' 
            << enemy_config.min_shape_vertices << ' ' 
            << enemy_config.max_shape_vertices << '\n'
            << bullet_config.shape_radius << ' ' 
            << bullet_config.collision_radius << ' ' 
            << bullet_config.speed << ' ' 
            << bullet_config.RGB_R << ' ' 
            << bullet_config.RGB_G << ' ' 
            << bullet_config.RGB_B << ' ' 
            << bullet_config.shape_vertices << ' ' 
            << bullet_config.lifespan << '\n';
*/
}

void Game_scene::sdl_initialize_window(SDL_Window* window, const char* const& window_title) 
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

  sdl_initialize_renderer(window);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Game_scene::sdl_initialize_renderer(SDL_Window* window)
{
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    throw std::runtime_error{"Game_scene::sdl_initialize_renderer(), renderer 가 nullptr 입니다."};
  }
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  quit = false;
  current_key_states = SDL_GetKeyboardState(nullptr);
  px = static_cast<float>(screen_width) * 0.5f;
  py = static_cast<float>(screen_height) * 0.5f;
  spawn_player();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool Game_scene::quitting()
{
  return quit;
}

void Game_scene::handle_event()
{
  while (SDL_PollEvent(&event) != 0) 
  {
    if (event.type == SDL_QUIT || current_key_states[SDL_SCANCODE_ESCAPE]) quit = true;
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        spawn_bullet( player, Vector2{ static_cast<float>(event.button.x), static_cast<float>(event.button.y) } );
      }
      if (event.button.button == SDL_BUTTON_RIGHT)
      {
        spawn_special_weapon( player, Vector2{ static_cast<float>(event.button.x), static_cast<float>(event.button.y) } );
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Game_scene::game_logic()
{
  // 60 FPS
  frame_start = SDL_GetTicks();
  
  handle_event();
  entities.update();
  render_system();
  input_system();
  movement_system();
  enemy_spawner_system();
  collision_system();
  liftspan_system();
  current_frame++;

  frame_time = SDL_GetTicks() - frame_start;
  if (frame_time < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frame_time);

  SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////////////////////////


void Game_scene::movement_system()
{
  
  // TODO: 이 함수에서 모든 엔터티 이동을 구현합니다.
  // player 가 움직이는지 확인하려면 player->Input_component 구성 요소를 읽어야 합니다.
  
  // player 이동
  player->transform->velocity = {0.0f, 0.0f};
  if (player->input->up) player->transform->velocity.y -= player_config.speed;
  if (player->input->left) player->transform->velocity.x -= player_config.speed;
  if (player->input->right) player->transform->velocity.x += player_config.speed;
  if (player->input->down) player->transform->velocity.y += player_config.speed;
  // 대각 이동 정규화
  if ( (player->input->up && player->input->left) || 
       (player->input->up && player->input->right) || 
       (player->input->down && player->input->left) || 
       (player->input->down && player->input->right) ) 
  {
    // 정규화 후, 스칼라(이동 속도)를 곱합니다.
    player->transform->velocity.normalize().scale(player_config.speed);
  }
  // player 의 위치 업데이트
  player->transform->position.x += player->transform->velocity.x;
  player->transform->position.y += player->transform->velocity.y;

  // 화면 밖으로 나가는걸 방지합니다.
  // screen width
  if ((player->transform->position.x - player->shape->radius) <= 0)
  {
    player->transform->position.x = player->shape->radius;
  }
  if ((player->transform->position.x + player->shape->radius) >= static_cast<float>(screen_width))
  {
    player->transform->position.x = static_cast<float>(screen_width) - player->shape->radius;
  }
  // screen height
  if ((player->transform->position.y - player->shape->radius) <= 0)
  {
    player->transform->position.y = player->shape->radius;
  }
  if ((player->transform->position.y + player->shape->radius) >= static_cast<float>(screen_height))
  {
    player->transform->position.y = static_cast<float>(screen_height) - player->shape->radius;
  }

  
  // Bullet 의 이동
  for (auto& e : entities.get_entities("bullet"))
  {
    e->transform->velocity.normalize().scale(bullet_config.speed);
    e->transform->position.x += e->transform->velocity.x;
    e->transform->position.y += e->transform->velocity.y;
  }
  for (auto& e : entities.get_entities("s_bullet"))
  {
    e->transform->velocity.normalize().scale(bullet_config.speed*2.0f);
    e->transform->position.x += e->transform->velocity.x;
    e->transform->position.y += e->transform->velocity.y;
  }
  // Enemy 이동
  for (auto& e : entities.get_entities("enemy"))
  {
    e->transform->position.x += e->transform->velocity.x;
    e->transform->position.y += e->transform->velocity.y;
  }
  // small enemies 의 이동
  for (auto& se : entities.get_entities("s_enemies"))
  {
    se->transform->position.x += se->transform->velocity.x;
    se->transform->position.y += se->transform->velocity.y;
  }

  // Enemy Entity 는 화면과 충돌 시 velocity 반전
  for (auto& e : entities.get_entities("enemy"))
  {
    // screen width
    if ((e->transform->position.x - e->shape->radius) <= 0)
    {
      e->transform->position.x = e->shape->radius;
      e->transform->velocity.x *= -1.0f;
    }
    if ((e->transform->position.x + e->shape->radius) >= static_cast<float>(screen_width))
    {
      e->transform->position.x = static_cast<float>(screen_width) - e->shape->radius;
      e->transform->velocity.x *= -1.0f;
    }
    // screen height
    if ((e->transform->position.y - e->shape->radius) <= 0)
    {
      e->transform->position.y = e->shape->radius;
      e->transform->velocity.y *= -1.0f;
    }
    if ((e->transform->position.y + e->shape->radius) >= static_cast<float>(screen_height))
    {
      e->transform->position.y = static_cast<float>(screen_height) - e->shape->radius;
      e->transform->velocity.y *= -1.0f;
    }
  }


  
  
}

void Game_scene::liftspan_system()
{
  
  /*
    TODO: 모든 수명 기능 구현

    모든 Entity 에 대해

    Entity 에 liftspan component가 없으면 건너뜁니다.
    Entity 의 남은 수명(liftspan) 이 > 0 인 경우 1을 빼십시오.
    수명이 있고 살아있다면
    알파(alpha) 채널의 크기를 적절하게 조정하세요.
    수명이 있고 시간(time)이 다 되었을 경우
    Entity 를 파괴
  */
  
  // bullet 수명
  for (auto& b : entities.get_entities())
  {
    if (!b->lifespan) continue;  // Life component 가 없는 Entity 건너뛰기
    b->lifespan->remaining--;
    // rgb 의 alpha 조정
    if (b->get_tag() == "bullet") b->shape->RGB_alpha -= 1;
    else if (b->get_tag() == "s_enemies") b->shape->RGB_alpha -= 2;
    
    if (b->lifespan->remaining <= 0 && b->get_tag() == "s_bullet")
    {
      blackhole(b);
    }
    
    if (b->lifespan->remaining <= 0)
    {
      b->destroy();
    }
  }
}

void Game_scene::collision_system()
{
  // TODO: Entities 간의 모든 적절한 충돌(collision)을 구현합니다.
  // 모양 반경(shape radius)이 아닌 충돌 반경(collision radius)을 사용해야 합니다.
  
  // player, enemy 충돌
  for (auto& p : entities.get_entities("player"))
  {
    for (auto& e : entities.get_entities("enemy"))
    {
      if (check_collision(p, e))
      {
        spawn_small_enemimes(e);
        p->destroy();
        e->destroy();
      }
    }
    if (!p->is_active())
    {
      // 센터에 player 재 생성
      spawn_player();
    }
  }

  // bullet, enemy 충돌
  for (auto& b : entities.get_entities("bullet"))
  {
    for (auto& e : entities.get_entities("enemy"))
    {
      if (check_collision(b, e))
      {
        // bullet, enemy
        spawn_small_enemimes(e);
        b->destroy();
        e->destroy();
      }
    }
  }
  // special bullet(blackhole), enemy 충돌
  for (auto& bh : entities.get_entities("blackhole"))
  {
    for (auto& e : entities.get_entities("enemy"))
    {
      if (check_collision(bh, e))
      {
        e->transform->velocity = bh->transform->position - e->transform->position;
        e->transform->velocity.normalize().scale(10.0f);
        if (bh->lifespan->remaining <= 5) e->destroy();
      }
    }
  }
  
}
// 두 Entity 의 충돌을 감지하는 함수
bool Game_scene::check_collision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
  float dis = e1->transform->position.distance(e2->transform->position);
  if ( ( dis < (e1->collision->radius + e2->collision->radius) ) )
  {
    return true;
  }
  return false;
}

void Game_scene::input_system()
{
  // TODO: 여기서 사용자 입력을 처리합니다.
  /* 
    여기서는 player 의 input component 변수만 설정해야 한다는 점에 유의하세요.
    여기서는 player 의 이동(movement) 논리를 구현하면 안 됩니다.
    movement system 은 이 기능에서 설정한 변수를 읽습니다.
  */

  // wasd 이동
  player->input->up = current_key_states[SDL_SCANCODE_W];
  player->input->left = current_key_states[SDL_SCANCODE_A];
  player->input->down = current_key_states[SDL_SCANCODE_S];
  player->input->right = current_key_states[SDL_SCANCODE_D];
}

void Game_scene::render_system()
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);

  for (auto& e : entities.get_entities())
  {
    // render geometry
    SDL_SetRenderDrawColor(renderer, e->shape->RGB_R, e->shape->RGB_G, e->shape->RGB_B, e->shape->RGB_alpha);
    e->transform->angle += 0.03f;
    draw_polygon(renderer, e->transform->position, e->shape->radius, e->shape->sides, e->transform->angle);
  }
}

void Game_scene::enemy_spawner_system()
{
  /*
    TODO: 적 생성을 구현하는 코드는 여기에 있어야 합니다.
    
    (current_frame - last_enemy_spawn_time) 을 사용하여 결정
    마지막 적이 생성된 이후 얼마나 지났는가
  */
  if (current_frame - last_enemy_spawn_time >= 60)
  {
    spawn_enemy();
    current_frame = 0;
  }
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Game_scene::spawn_player()
{
  // TODO: config에서 올바른 값으로 플레이어의 모든 속성을 추가 완료
  
  /*
    우리는 모든 Entity 를 entity_manager.add_entity(tag)를 호출하여 생성합니다.
    이것은 std::shared_ptr<Entity>를 반환하므로 'auto'를 사용하여 입력을 저장합니다.
  */
  auto entity = entities.add_entity("player");

  // 이 Entity에 Transform 을 제공하여 (200, 200) Position에 Velocity(1,1) 및 angle 0으로 생성되도록 합니다.
  entity->transform = std::make_shared<Transform_component>(Vector2{px, py}, Vector2{1.0f, 1.0f}, 0.0f);

  // Entity 모양은 radius 32, sides 8개, 어두운 회색 fill, outline 4 의 빨간색 thickness을 갖습니다.
  // 빨간색 thickness 만 사용
  entity->shape = std::make_shared<Shape_component>(player_config.shape_radius, 
                                                    player_config.shape_vertices, 
                                                    player_config.RGB_R, 
                                                    player_config.RGB_G, 
                                                    player_config.RGB_B, 0xFF);

  // 플레이어에 입력 구성요소를 추가하여 입력을 사용할 수 있도록 합니다.
  entity->input = std::make_shared<Input_component>();
  entity->collision = std::make_shared<Collision_component>(player_config.collision_radius);

  /*
    Siene 우리는 이 Entity 를 플레이어로 만들고 싶고, 우리 게임의 플레이어 변수를 이 Entity 로 설정합니다.
    이는 Entity_manager 패러다임에 약간 어긋나지만, 우리는 플레이어를 너무 많이 사용하기 때문에 가치가 있습니다.
  */
  player = entity;
}

// 무작위 위치에 Enemy 를 생성합니다
void Game_scene::spawn_enemy()
{
  /*
    TODO: 
    enemy_config 변수로 Enemy 이 제대로 생성되었는지 확인하세요.
    Enemy 은 창의 경계 내에서 완전히 생성되어야 합니다.
  */
  
  auto entity = entities.add_entity("enemy");

  float ex = static_cast<float>(rand() % screen_width);
  float ey = static_cast<float>(rand() % screen_height);
  

  // 날아가는 방향(direction)
  float dx = -static_cast<float>(screen_width) + static_cast<float>( (rand() % ( 1 + screen_width - (-screen_width) )) );
  float dy = -static_cast<float>(screen_height) + static_cast<float>( (rand() % ( 1 + screen_height - (-screen_height) )) );

  Vector2 dir = {dx, dy};
  int random_length = enemy_config.min_speed + ( rand() % (1 + enemy_config.max_speed - enemy_config.min_speed) );
  dir.normalize().scale(static_cast<float>(random_length));

  // 이 Entity에 Transform 을 제공하여 (200, 200) Position에 Velocity(1,1) 및 angle 0으로 생성되도록 합니다.
  entity->transform = std::make_shared<Transform_component>(Vector2{ex, ey}, dir, 0.0f);

  // 3 ~ 8 각형
  int random_sides = enemy_config.min_shape_vertices + ( rand() % (1 + enemy_config.max_shape_vertices - enemy_config.min_shape_vertices) );
  // 랜덤 색상
  Uint8 random_color1 = static_cast<Uint8>(enemy_config.min_RGB_range + (rand() % (1+ enemy_config.max_RGB_range - enemy_config.min_RGB_range)));
  Uint8 random_color2 = static_cast<Uint8>(enemy_config.min_RGB_range + (rand() % (1+ enemy_config.max_RGB_range - enemy_config.min_RGB_range)));
  Uint8 random_color3 = static_cast<Uint8>(enemy_config.min_RGB_range + (rand() % (1+ enemy_config.max_RGB_range - enemy_config.min_RGB_range)));
  // 랜덤 thickness 만 사용
  entity->shape = std::make_shared<Shape_component>(16.0f, random_sides, random_color1, random_color2, random_color3, 0xFF);
  entity->collision = std::make_shared<Collision_component>(16.0f);

  // 가장 최근의 Enemy 이 생성된 시점을 기록하세요.
  //last_enemy_spawn_time = current_frame;
}

// 큰 Enemy (입력 Entity e)이 폭발하면 작은 Enemies 가 생성됩니다.
void Game_scene::spawn_small_enemimes(std::shared_ptr<Entity> entity)
{
  // TODO: 입력된 Enemy e 위치에 작은 Enemies 를 생성합니다.

  /*
    // 더 작은 적을 생성할 때는 원래 적의 값을 읽어야 합니다.
     - 원래 적의 정점과 같은 수의 작은 적을 생성합니다.
     - 각각의 작은 적을 원본과 같은 색상으로 설정하고 크기는 절반으로 줄입니다.
     - 작은 적은 원래 적의 포인트의 두 배에 해당합니다.
  */
  float step = static_cast<float>(2 * M_PI / entity->shape->sides);
  float dis = entity->transform->velocity.length() * 0.353553f;
  for (int i = 0; i < entity->shape->sides; ++i)
  {
    auto small_enemies = entities.add_entity("s_enemies");
    
    float vel_x = entity->shape->radius * std::cosf(static_cast<float>(i) * step + entity->transform->angle);
    float vel_y = entity->shape->radius * std::sinf(static_cast<float>(i) * step + entity->transform->angle);

    Vector2 velocity = {vel_x, vel_y};
    velocity.normalize().scale(dis);
    
    small_enemies->transform = std::make_shared<Transform_component>(entity->transform->position, velocity, 0.0f);
    small_enemies->shape = std::make_shared<Shape_component>(entity->shape->radius*0.5f, entity->shape->sides, 
                                                             entity->shape->RGB_R, 
                                                             entity->shape->RGB_G, 
                                                             entity->shape->RGB_B, 0xFF);
    small_enemies->collision = std::make_shared<Collision_component>(entity->shape->radius*0.5f);
    small_enemies->lifespan = std::make_shared<Lifespan_component>(57);
  }
}

void Game_scene::spawn_bullet(std::shared_ptr<Entity> entity, const Vector2& target)
{
  // TODO: 타겟을 향해 날아가는 총알의 생성을 구현합니다.
  // 총알 속도는 스칼라 속도로 주어집니다.
  // 노트에 있는 공식을 사용하여 속도를 설정해야 합니다.

  auto bullet = entities.add_entity("bullet");

  bullet->transform = std::make_shared<Transform_component>(entity->transform->position, 
                                                            Vector2{target - entity->transform->position}, 0.0f);
  bullet->shape = std::make_shared<Shape_component>(bullet_config.shape_radius, 
                                                    bullet_config.shape_vertices, 
                                                    bullet_config.RGB_R, 
                                                    bullet_config.RGB_G, 
                                                    bullet_config.RGB_B, 0xFF);
  bullet->collision = std::make_shared<Collision_component>(bullet_config.collision_radius);
  bullet->lifespan = std::make_shared<Lifespan_component>(bullet_config.lifespan);
}

void Game_scene::spawn_special_weapon(std::shared_ptr<Entity> entity, const Vector2& target)
{
  // TODO: 당신만의 특별한 무기를 구현하세요.
  auto special_bullet = entities.add_entity("s_bullet");

  special_bullet->transform = std::make_shared<Transform_component>(entity->transform->position, 
                                                                    Vector2{target - entity->transform->position}, 
                                                                    0.0f);
  special_bullet->shape = std::make_shared<Shape_component>(150.0f, 8, 0xA4, 0xC4, 0xEE, 0xFF);
  special_bullet->collision = std::make_shared<Collision_component>(10.0f);
  special_bullet->lifespan = std::make_shared<Lifespan_component>(30);
}
void Game_scene::blackhole(std::shared_ptr<Entity> bullet)
{
  auto blackhole = entities.add_entity("blackhole");
  blackhole->transform = std::make_shared<Transform_component>(bullet->transform->position, Vector2{0.0f, 0.0f}, 0.0f);
  blackhole->shape = std::make_shared<Shape_component>(10.0f, 8, 0xA4, 0xC4, 0xEE, 0xFF); 
  blackhole->collision = std::make_shared<Collision_component>(150.0f);
  blackhole->lifespan = std::make_shared<Lifespan_component>(300);
}


///////////////////////////////////////////////////////////////////////////////////////////////////

// 정다각형을 그리는 함수
void Game_scene::draw_polygon(SDL_Renderer* renderer, Vector2& pos, float& radius, int& sides, float& angle)
{
  float step = static_cast<float>(2 * M_PI / sides);
  SDL_FPoint points[sides+1];
  for (int i = 0; i < sides; ++i)
  {
    points[i].x = pos.x + radius * std::cosf(static_cast<float>(i) * step + angle);
    points[i].y = pos.y + radius * std::sinf(static_cast<float>(i) * step + angle);
  }
  points[sides] = points[0];
  SDL_RenderDrawLinesF(renderer, points, sides+1);
}
