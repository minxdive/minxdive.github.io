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
  Uint8 RGB_R = 0, RGB_G = 0, RGB_B = 0, RGB_alpha = 0;
  
  Shape_component(float rad, int si, Uint8 R, Uint8 G, Uint8 B, Uint8 alpha)
    : radius(rad), sides(si), 
      RGB_R(R), RGB_G(G), RGB_B(B) , 
      RGB_alpha(alpha) { }
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
