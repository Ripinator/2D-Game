#ifndef DEFAULT_SWORD_HPP
#define DEFAULT_SWORD_HPP

#include "gear/weapon.hpp"

#define NUM_ATTACKS 8

enum class AnimationState
{
  Idle = 8,
  Walk = 8,
  Jumping = 5,
  AttackMouseLeft = 14
};

class DefaultSword : public Weapon
{
  private:
    int base_damage_;
    WeaponType weapon_type_;
    std::array<SDL_FRect, NUM_ATTACKS> attack_hitboxes_;
    std::unordered_map<AnimationState, int> frame_counts_;

  public:
    DefaultSword(WeaponType weapon_type, std::array<SDL_FRect, NUM_ATTACKS> attack_hitboxes);
    
    std::array<SDL_FRect, NUM_ATTACKS> get_hitboxes();

};

#endif