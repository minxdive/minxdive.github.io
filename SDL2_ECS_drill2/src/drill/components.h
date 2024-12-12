#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "vector2.h"
#include "animation.h"

class Component {
public:
  bool has = false;
};

class Transform_component : public Component {
public:
  Vector2 position = {0.0f, 0.0f};
  Vector2 velocity = {0.0f, 0.0f};
  Vector2 init_pos = {0.0f, 0.0f};
  Vector2 prev_pos = {0.0f, 0.0f};

  Transform_component() { }
  Transform_component(const Vector2& pos) 
    : position(pos) { }
  Transform_component(const Vector2& pos, const Vector2& vel)
    : position(pos), velocity(vel), init_pos(pos) { }
};

class Input_component : public Component {
public:
  bool left = false;
  bool right = false;
  bool jumping = false;
  bool can_jump = false;
  std::string jump_state = "NOT_JUMP";

  Input_component() { }
};

class Font_component : public Component {
public:
  std::string text_string;
  SDL_Surface* font_surface = nullptr;
  SDL_Texture* font_texture = nullptr;
  SDL_Color    font_color = {0x00, 0x00, 0x00};
  SDL_Rect     font_rect = {1,1,1,1};
  Font_component() { }
  Font_component(TTF_Font*& font, const std::string& content, SDL_Color color, SDL_Renderer*& renderer, SDL_Rect rect)
    : text_string(content), font_color(color), font_rect(rect)
  { 
    font_surface = TTF_RenderText_Solid(font, text_string.c_str(), color);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_FreeSurface(font_surface);
  }
  void index_color_update(TTF_Font*& font, SDL_Renderer*& renderer, size_t& index, const size_t& n)
  {
    SDL_DestroyTexture(font_texture);  // 이전 텍스처는 삭제해야 메모리 낭비를 막을 수 있음
    font_surface = nullptr;
    font_texture = nullptr;
    if (index != n) { font_color = { 0x64, 0x64, 0x64 }; }
    else { font_color = { 0xFF, 0xFF, 0xFF }; }
    font_surface = TTF_RenderText_Solid(font, text_string.c_str(), font_color);
    font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    SDL_FreeSurface(font_surface);
  }
};

class Animation_component : public Component {
public:
  Animation animation;
  bool flip = false;
  Animation_component() { }
  Animation_component(Animation ani, bool flp) : animation(ani), flip(flp) { }
};

class Bounding_box_component : public Component {
public:
  Vector2 size;
  Vector2 half_size;
  Bounding_box_component() { }
  Bounding_box_component(const Vector2& siz)
    : size(siz), half_size(Vector2{siz.x/2, siz.y/2}) { }
};

class Gravity_component : public Component {
public:
  float gravity = 1.0f;
  Gravity_component() { }
};

class State_component : public Component {
public:
  std::string name = "";
  std::string state = "";
  State_component() { }
  State_component(const std::string& nam, const std::string& sta) : name(nam), state(sta) { }
};

#endif