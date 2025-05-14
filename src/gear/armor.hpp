#ifndef ARMOR_HPP
#define ARMOR_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "window.hpp"
#include "scene.hpp"

enum class ArmorType
{
  Boots = 0,
  Legs = 1,
  Belt = 2,
  Chest = 3,
  Helmet = 4
};

class Armor
{
  protected:
    SDL_Renderer *renderer_;
    SDL_Texture *sprite_;
    SDL_Surface *sprite_surface_;
};

#endif