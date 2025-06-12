#include "gear/weapon.hpp"

Weapon::Weapon(SDL_Renderer *renderer)
 : renderer_(renderer), base_damage_(0), rarity_(0.0f), current_frame_(0),
   animation_time_(0.0f), animation_speed_(100.0f), is_attacking_(false) {}

Weapon::~Weapon()
{
  if(sprite_)
  {
    SDL_DestroyTexture(sprite_);
  }
}
