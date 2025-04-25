#ifndef TILE_HPP
#define TILE_HPP

#include <SDL2/SDL.h>

struct Tile {
  SDL_Texture *texture;
  SDL_FRect destRect;
  bool solid;
};

#endif
