#include "night_borne.hpp"

NightBorne::NightBorne(Window &window, int x, int y, const SDL_Rect &floor_rect)
: Enemy(window, floor_rect)
{
  health_ = 200;
  damage_ = 15;
  speed_ = 4;
  SDL_Surface *sprite_surface_ = IMG_Load("assets/NightBorne.png");
  sprite_ = SDL_CreateTextureFromSurface(renderer_, sprite_surface_);
  SDL_FreeSurface(sprite_surface_);

  enemy_rect_.x = x;
  enemy_rect_.y = y;
  enemy_rect_.w = 64;
  enemy_rect_.h = 64;

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