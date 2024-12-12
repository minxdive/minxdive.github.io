#include <print>
#include "animation.h"

Animation::Animation(const std::string& name, const size_t& sp, int sx, int sy, float wid, float hei)
  : current_frame(0), speed(sp), size_x(sx), size_y(sy), width(wid), height(hei)
{
  
}


/////////////////////////////////////////////////////////////////////////////////////////////////

void Animation::add_state(const std::string& sta, const size_t& cnt, const int pos_x, const int pos_y)
{
  state = sta;
  frame_count = cnt;
  for (size_t i = 0; i < cnt; ++i) {
    src_rec_vec.push_back(SDL_Rect{static_cast<int>(i)*size_x + pos_x, pos_y, size_x, size_y});
  }
  sta_rec_map[state] = src_rec_vec;
  src_rec_vec.clear();
  sta_fra_map[state] = frame_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Animation::update(SDL_Renderer*& renderer, Assets*& assets_ptr, const std::string& name, const std::string& sta, Vector2 pos, bool ani, bool flip)
{
  if (pos.x > 864.0f) return;
  
  std::vector<SDL_Rect>& src = sta_rec_map.at(sta);
  size_t& fra_cnt = sta_fra_map.at(sta);
  SDL_FRect dst = {pos.x, pos.y, width, height};
  
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  current_frame++;
  size_t ani_frame = (current_frame / speed) % fra_cnt;

  if (!flip) {
    SDL_RenderCopyF(renderer, assets_ptr->get_sprite(name), &src[ani_frame], &dst);
  }
  else if (flip) {
    SDL_RenderCopyExF(renderer, assets_ptr->get_sprite(name), &src[ani_frame], &dst, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
  }
}