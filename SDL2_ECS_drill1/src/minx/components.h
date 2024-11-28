/*
  구성요소(Component) 들을 모아놓은 파일
*/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "SDL2/SDL.h"

#include "vector2.h"

class Transform_component 
{
public:
  Vector2 position = {0.0f, 0.0f};
  Vector2 velocity = {0.0f, 0.0f};
  float   angle    = 0.0f;

  Transform_component(const Vector2& pos, const Vector2& vel, float ang)
    : position(pos), velocity(vel), angle(ang) { }
};

class Shape_component 
{
public:
  float radius = 0.0f;
  int sides = 0;
  Uint8 fill_color_r = 0, fill_color_g = 0, fill_color_b = 0, alpha = 0;
  
  Shape_component(float rad, int si, Uint8 fcr, Uint8 fcg, Uint8 fcb, Uint8 alp)
    : radius(rad), sides(si), fill_color_r(fcr), fill_color_g(fcg), fill_color_b(fcb) , alpha(alp)
  {
    
  }
};

class Collision_component
{
public:
  float radius = 0.0f;
  Collision_component(float rad) : radius(rad) { }
};

class Score_component
{
public:
  int score = 0;
  Score_component(int s) : score(s) { }
};

class Lifespan_component
{
public:
  int remaining = 0;  // Entity 의 남은 수명(lifespan)
  int total = 0;  // 총 초기 수명
  Lifespan_component(int total)
    : remaining(total), total(total) { }
};

class Input_component
{
public:
  bool up    = false;
  bool left  = false;
  bool right = false;
  bool down  = false;
  bool shoot = false;

  Input_component() { }
};

#endif
