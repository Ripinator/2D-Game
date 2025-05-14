#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scene.hpp"
#include "window.hpp"
#include <array>
#include <unordered_map>

enum class WeaponType
{
  NoItem = 0,
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
    SDL_Rect src_rect_;
    SDL_Rect dest_rect_;
    float rarity_;
    float base_damage_;
    int frame_width_;
    int frame_height_;
    int current_frame_;
    float animation_time_;
    float animation_speed_;
    bool is_attacking_;

  public:
    Weapon(SDL_Renderer *renderer);
    virtual ~Weapon() = default;

    virtual void attack() = 0;
    virtual void render(float player_x_, float player_y, SDL_RendererFlip flip) = 0;
};

#endif