#include "no_sword.hpp"
#include <iostream>

NO_SWORD::NO_SWORD(SDL_Renderer *renderer) 
 : Weapon(renderer)
{
  for (auto &box : attack_hitboxes_)
  {
    box = {0, 0, 0, 0};
  }

  weapon_type_ = WeaponType::Sword;
  base_damage_ = 1;
  rarity_ = 0.6;
  frame_height_ = 64;
  frame_width_ = 64;
  attack_animation_done_ = true;
  attack_timer_ = 0.0f;
  move_x_ = 0.0f;
  move_y_ = 0.0f;
  velocity_x_ = 0.0f;
  velocity_y_ = 0.0f;
  player_speed_ = 400.0f;
  is_jumping_ = false;

  src_rect_ = {0, 0, 64, 64};
  dest_rect_ = {0, 0, 64 * 3, 64 * 3};

  frame_counts_[AnimationStateNoSword::Idle] = 8;
  frame_counts_[AnimationStateNoSword::Walk] = 8;
  frame_counts_[AnimationStateNoSword::Jump] = 11;
  frame_counts_[AnimationStateNoSword::AttackLMB] = 5;

  sprite_surface_ = IMG_Load("assets/player/swords/player_no_items.png");
  sprite_ = SDL_CreateTextureFromSurface(renderer_, sprite_surface_);
  SDL_FreeSurface(sprite_surface_);

  attack_hitboxes_[0].w = (frame_width_ / 3) * 2;
  attack_hitboxes_[0].h = (frame_height_ / 3) * 2;
}

bool NO_SWORD::get_current_frame()
{
  return current_frame_;
}

void NO_SWORD::set_current_frame(int current_frame)
{
  current_frame_ = current_frame;
}

bool NO_SWORD::get_animation_timer()
{
  return animation_time_;
}

void NO_SWORD::set_animation_timer(float animation_time)
{
  animation_time_ = animation_time;
}

bool NO_SWORD::get_attack_animation_done()
{
  return attack_animation_done_;
}

void NO_SWORD::set_attack_animation_done(bool attack_animation_done)
{
  attack_animation_done_ = attack_animation_done;
}

bool NO_SWORD::get_attacking()
{
  return is_attacking_;
}

void NO_SWORD::set_attacking(bool is_attacking)
{
  is_attacking_ = is_attacking;
}

void NO_SWORD::animate(float delta_time, std::any animation_state_any)
{
  try
  {
    AnimationStateNoSword animation_state = assignAnimationState(std::any_cast<PlayerState>(animation_state_any));
    animation_state_ = animation_state;

    animation_time_ += delta_time * 1000.0f;
    if (animation_time_ >= animation_speed_)
    {
      int max_frames = frame_counts_[animation_state];
      current_frame_++;

      if (animation_state == AnimationStateNoSword::AttackLMB && current_frame_ >= max_frames)
      {
        is_attacking_ = false;
        attack_animation_done_ = true;
        current_frame_ = 0;
        animation_state = AnimationStateNoSword::Idle;
      }
      else
      {
        current_frame_ %= max_frames;
      }

      animation_time_ = 0.0f;
    }
  }
  catch(const std::bad_any_cast &e)
  {
    std::cerr << "ERROR: INVALID animation state in default sword" << "Exception: " << e.what() << std::endl;
  }
}

AnimationStateNoSword NO_SWORD::assignAnimationState(PlayerState animation_state)
{
  AnimationStateNoSword current_animation_frame_count;

  switch (animation_state)
  {
  case (PlayerState::Idle):
    current_animation_frame_count = AnimationStateNoSword::Idle;
    break;

  case (PlayerState::Walk):
    current_animation_frame_count = AnimationStateNoSword::Walk;
    break;

  case (PlayerState::Jumping):
    current_animation_frame_count = AnimationStateNoSword::Jump;
    break;
    
  case (PlayerState::AttackLMB):
    current_animation_frame_count = AnimationStateNoSword::AttackLMB;
    break;

  default:
    current_animation_frame_count = AnimationStateNoSword::Idle;
    break;
  }

  return current_animation_frame_count;
}

void NO_SWORD::update(float delta_time)
{}

SDL_FRect NO_SWORD::getAttackCollisionBox() const
{
  return collision_box_;
}

void NO_SWORD::render(SDL_RendererFlip flip)
{
  src_rect_.x = current_frame_ * (frame_width_ + 16);
  src_rect_.y = static_cast<int>(animation_state_) * frame_height_;
  src_rect_.w = frame_width_;
  src_rect_.h = frame_height_;

  dest_rect_.x = collision_box_.x;
  dest_rect_.y = collision_box_.y + 905.0f;
  dest_rect_.w = frame_width_ * 3;
  dest_rect_.h = frame_height_ * 3;

  if (flip == SDL_FLIP_NONE)
  {
    dest_rect_.x = collision_box_.x + 1090.0f;
  }
  else if (flip == SDL_FLIP_HORIZONTAL)
  {
    dest_rect_.x = collision_box_.x + 1152.0f;
  }

  SDL_RenderCopyExF(renderer_, sprite_, &src_rect_, &dest_rect_, 0, nullptr, flip);
}
