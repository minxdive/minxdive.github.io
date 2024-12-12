#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include <map>
#include <vector>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

class Assets {
  std::map<std::string, TTF_Font*> fon_map;
  TTF_Font* font;
  std::map<std::string, SDL_Texture*> spr_map;
  SDL_Texture* sprite;
public:
  
  Assets();
  ~Assets();

  void add_font(const std::string& name, const std::string& path);
  TTF_Font*& get_font(const std::string& name);

  void add_sprite(SDL_Renderer*& renderer, const std::string& name, const std::string& path);
  SDL_Texture*& get_sprite(const std::string& name);
};

#endif