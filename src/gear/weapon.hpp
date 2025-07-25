#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "scene.hpp"
#include "window.hpp"
#include <array>
#include <unordered_map>
#include <any>

enum class WeaponType
{
  NoItem = 0,
  Sword = 1,
  Bow = 2,
  Wand = 3
};

enum class Swords
{
  DefaultSword,
  SamuraiSword
};

class Weapon
{
  protected:
    SDL_Renderer *renderer_;
    SDL_Texture *sprite_;
    SDL_Surface *sprite_surface_;
    SDL_Rect src_rect_;
    SDL_FRect dest_rect_;
    SDL_FRect collision_box_;
    //std::array<SDL_FRect, 100> attack_collision_boxes_;
    WeaponType weapon_type_;
    bool attack_animation_done_;
    float attack_timer_;
    float rarity_;
    float base_damage_;
    int frame_width_;
    int frame_height_;
    int current_frame_;
    float animation_time_;
    float animation_speed_;
    bool is_attacking_;
    float velocity_x_;
    float velocity_y_;
    float move_x_;
    float move_y_;
    float player_speed_;
    bool is_jumping_;

  public:
    Weapon(SDL_Renderer *renderer);
    virtual ~Weapon();

    virtual bool get_animation_timer() = 0;
    virtual void set_animation_timer(float animation_timer) = 0;
    virtual bool get_current_frame() = 0;
    virtual void set_current_frame(int current_frame) = 0;
    virtual bool get_attack_animation_done() = 0;
    virtual void set_attack_animation_done(bool attack_animation_done) = 0;
    virtual bool get_attacking() = 0;
    virtual void set_attacking(bool is_attacking) = 0;
    
    virtual void update(float delta_time) = 0;
    virtual void render(SDL_RendererFlip flip) = 0;
    virtual void animate(float delta_time, std::any animation_state) = 0;
    virtual std::array<SDL_FRect, 100> getAttackCollisionBox() const = 0;
};

#endif
