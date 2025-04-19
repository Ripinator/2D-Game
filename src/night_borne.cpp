#include "night_borne.hpp"

NightBorne::NightBorne(Window &window, const SDL_Rect &floor_rect)
: Enemy(window, floor_rect)
{
  health_ = 200;
  damage_ = 15;
  speed_ = 4;
  sprite_surface_ = IMG_Load("assets/NightBorne.png");
  sprite_ = SDL_CreateTextureFromSurface(renderer_, sprite_surface_);
  SDL_FreeSurface(sprite_surface_);

  frame_counts_[EnemyState::Idle] = 9;
  frame_counts_[EnemyState::Walking] = 6;
  frame_counts_[EnemyState::Attack] = 12;
  frame_counts_[EnemyState::IsHit] = 5;
  frame_counts_[EnemyState::IsDead] = 23; 
}

void NightBorne::update()
{

}

void NightBorne::render()
{
  
}