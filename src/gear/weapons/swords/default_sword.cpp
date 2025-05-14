#include "default_sword.hpp"

DefaultSword::DefaultSword(WeaponType weapon_type, std::array<SDL_FRect, NUM_ATTACKS> attack_hitboxes) 
 : weapon_type_(weapon_type), attack_hitboxes_(attack_hitboxes)
{
  for (auto &box : attack_hitboxes_)
  {
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
  }

  weapon_type_ = WeaponType::Sword;
  base_damage_ = 1;
  rarity_ = 0.6;

  frame_counts_[AnimationState::Idle] = 8;
  frame_counts_[AnimationState::Walk] = 8;
  frame_counts_[AnimationState::Jumping] = 11;
  frame_counts_[AnimationState::AttackMouseLeft] = 5;

  sprite_surface_ = IMG_Load("assets/player/swords/default_sword.png");
  sprite_ = SDL_CreateTextureFromSurface(renderer_, sprite_surface_);
  SDL_FreeSurface(sprite_surface_);

  set_hitboxes(attack_hitboxes_);
}

// I set the attack hitboxes to hardcoded values because they differ in none
// obvious ways depending on the attack and weapon
void set_hitboxes(std::array<SDL_FRect, NUM_ATTACKS> attack_hitboxes)
{
  int frame_width, frame_height = 64;

  attack_hitboxes[0].w = (frame_width / 3) * 2;
  attack_hitboxes[0].h = (frame_height / 3) * 2;
}

std::array<SDL_FRect, NUM_ATTACKS> DefaultSword::get_hitboxes()
{
  return attack_hitboxes_;
}

