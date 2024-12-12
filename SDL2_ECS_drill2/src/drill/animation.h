#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>
#include <map>
#include "SDL2/SDL.h"
#include "vector2.h"
#include "assets.h"

class Animation {
  std::string  state;                  // 애니메이션 상태
  size_t       frame_count = 1;        // 애니메이션 프레임 총 개수
  size_t       current_frame = 0;      // 재생 중인 애니메이션의 현재 프레임
  size_t       speed = 0;              // 이 애니메이션을 재생하는 속도
  int          size_x = 0, size_y = 0; // 스프라이트 크기
  float width = 0.0f, height = 0.0f;   // 화면에 표시할 픽셀의 크기
  std::vector<SDL_Rect> src_rec_vec;   // 스프라이트 위치, 크기
  std::map<std::string, std::vector<SDL_Rect>> sta_rec_map;  // 상태, 애니메이션 배열 저장
  std::map<std::string, size_t> sta_fra_map;  // 상태, 프레임 저장

public:
  Animation() { }
  // Assets 포인터, 상태, 프레임 스피드
  Animation(const std::string& name, const size_t& sp, int sx, int sy, float wid, float hei);
  
  // pos_x, pos_y: 로드할 스프라이트의 위치
  void add_state(const std::string& sta, const size_t& cnt, const int pos_x, const int pos_y);

  void update(SDL_Renderer*& renderer, Assets*& assets_ptr, const std::string& name, const std::string& sta, Vector2 pos, bool ani, bool flip = false);
  
};

#endif