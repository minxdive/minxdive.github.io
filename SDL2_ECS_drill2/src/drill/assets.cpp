#include <print>
#include "assets.h"

Assets::Assets()
{
  std::print("Assets");
}

Assets::~Assets()
{
  if (font != nullptr) {
    for (auto& f : fon_map) {
      TTF_CloseFont(f.second);
    }
    fon_map.clear();
    font = nullptr;
  }
  if (sprite != nullptr) {
    for (auto& sp : spr_map) {
      SDL_DestroyTexture(sp.second);
    }
    spr_map.clear();
    sprite = nullptr;
  }

  std::print("~Assets");
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Assets::add_font(const std::string& name, const std::string& path)
{
  font = TTF_OpenFont(path.c_str(), 16);
  fon_map[name] = font;
}

TTF_Font*& Assets::get_font(const std::string& name)
{
  return fon_map.at(name);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Assets::add_sprite(SDL_Renderer*& renderer, const std::string& name, const std::string& path)
{
  sprite = IMG_LoadTexture(renderer, path.c_str());
  spr_map[name] = sprite;
}

SDL_Texture*& Assets::get_sprite(const std::string& name)
{
  return spr_map.at(name);
}