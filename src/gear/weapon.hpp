#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scene.hpp"
#include "window.hpp"

enum class WeaponType
{
  Sword = 1,
  Bow = 2,
  Wand = 3
};

class Weapon
{
  protected:
    SDL_Renderer *renderer_;
    SDL_Texture *sprite_;
    SDL_Surface *sprite_surface_;
    float rarity_;
    float base_damage_;

  public:

};

#endif