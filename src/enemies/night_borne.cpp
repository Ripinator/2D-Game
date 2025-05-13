#include "night_borne.hpp"

NightBorne::NightBorne(Window &window, int x, int y, const SDL_Rect &floor_rect)
: Enemy(window, floor_rect)
{
  frame_width_ = 64;
  frame_height_ = 64;
  velocity_x_ = 0;
  velocity_y_ = 0;
  health_ = 200;
  damage_ = 15;
  speed_ = 1;
  sprite_surface_ = IMG_Load("assets/enemies/NightBorne.png");
  is_attacking_ = false;
  is_falling_ = false;
  animation_speed_ = 20;
  animation_timer_ = 0;
  flip_ = SDL_FLIP_NONE;
  wait = 0;
  move_x_ = 0.0f;
  move_y_ = 0.0f;
  health_ = 5;

  sprite_ = SDL_CreateTextureFromSurface(renderer_, sprite_surface_);
  SDL_FreeSurface(sprite_surface_);

  enemy_rect_.x = x;
  enemy_rect_.y = y;
  enemy_rect_.w = 64;
  enemy_rect_.h = 64;

  collision_box_.x = x;
  collision_box_.y = y;
  collision_box_.w = 64;
  collision_box_.h = 64;
  
  health_bar_.x = x;
  health_bar_.y = y;
  health_bar_.w = 54;
  health_bar_.h = 8;

  health_bar_border_.x = x;
  health_bar_border_.y = y;
  health_bar_border_.w = 56;
  health_bar_border_.h = 10;

  frame_counts_[EnemyState::Idle] = 9;
  frame_counts_[EnemyState::Walking] = 6;
  frame_counts_[EnemyState::Attack] = 12;
  frame_counts_[EnemyState::IsHit] = 5;
  frame_counts_[EnemyState::IsDead] = 23; 
}

void NightBorne::setTiles(std::vector<Tile> *tiles)
{
  tiles_ = tiles;
}

void NightBorne::animate(float delta_time)
{
  animation_timer_++;
  if (animation_timer_ >= animation_speed_)
  {
    int max_frames = frame_counts_[animation_state_];
    current_frame_++;
    current_frame_ %= max_frames;
    animation_timer_ = 0;
  }
}

void NightBorne::setEnemyPosition(int position_x, int position_y)
{
  collision_box_.x = position_x;
  collision_box_.y = position_y;
}

void NightBorne::update(const SDL_FRect &player_box, const std::array<SDL_FRect, 100> &player_attacks_hitboxes, float delta_time)
{
  const int detection_range = 200;
  int distance_to_player = player_box.x - collision_box_.x;

  // if (std::abs(distance_to_player) < detection_range)
  // {
  //   animation_state_ = EnemyState::Idle;
  //   velocity_x_ = 0;

  //   flip_ = (distance_to_player < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  // }
  // else
  // {
  //   animation_state_ = EnemyState::Walking;
  //   velocity_x_ = (distance_to_player > 0) ? enemy_speed_ : -enemy_speed_;
  //   move_x_ = velocity_x_ * delta_time;
  // }

  animate(delta_time);

  SDL_FRect future_position_x = {
    collision_box_.x + move_x_,
    collision_box_.y,
    collision_box_.w,
    collision_box_.h
  };

  if (tiles_)
  {
    for (const Tile &tile : *tiles_)
    {
      if (!tile.solid) continue;

      SDL_FRect tile_rect = tile.destRect;

      if (SDL_HasIntersectionF(&future_position_x, &tile_rect))
      {
        if (velocity_x_ > 0)
        {
          future_position_x.x = tile_rect.x - future_position_x.w;
        }
        else if (velocity_x_ < 0)
        {
          future_position_x.x = tile_rect.x + tile_rect.w;
        }
        velocity_x_ = 0;
        move_x_ = 0;
      }
    }
  }

  collision_box_.x += move_x_;

  SDL_FRect future_position_y = {
    collision_box_.x,
    collision_box_.y + velocity_y_,
    collision_box_.w,
    collision_box_.h
  };

  // iterating through every tile and checking if the object intersects with it 
  if (tiles_)
  {
    for (const Tile &tile : *tiles_)
    {
      if (!tile.solid) continue;

      SDL_FRect tile_rect = tile.destRect;

      if (SDL_HasIntersectionF(&future_position_y, &tile_rect))
      {
        if (velocity_y_ > 0)
        {
          future_position_y.y = tile_rect.y - future_position_y.h;
          is_falling_ = false;
        }
        else if (velocity_y_ < 0)
        {
          future_position_y.y = tile_rect.y + tile_rect.h;
        }
        velocity_y_ = 0;
        move_y_ = 0;
      }
    }
  }

  collision_box_.y = future_position_y.y;

  health_bar_.x = collision_box_.x;
  health_bar_.y = collision_box_.y - 35;
  health_bar_border_.x = health_bar_.x - 1;
  health_bar_border_.y = health_bar_.y - 1;
}

void NightBorne::setCameraOffset(int x, int y)
{
  camera_x_ = x;
  camera_y_ = y;
}

void NightBorne::render()
{
  SDL_Rect src_rect;
  src_rect.x = current_frame_ * (frame_width_ + 16);
  src_rect.w = frame_width_;
  src_rect.h = frame_height_;

  SDL_FRect dest_rect;
  dest_rect.w = frame_width_* 3;
  dest_rect.h = frame_height_ * 3;

  // there are some seemingly random hardcoded values in here because the spritesheet is weird and iam to lazy to change the sheet itself
  // also maybe a switch statement is not the optimale solution but i dont care
  switch (animation_state_)
  {
    case EnemyState::Idle:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_;
      dest_rect.y = collision_box_.y - camera_y_ - 128;
      break;
    case EnemyState::Walking:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 32;
      dest_rect.y = collision_box_.y - camera_y_ - 80;
      break;
    case EnemyState::Attack:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 32;
      dest_rect.y = collision_box_.y - camera_y_ - 128;
      break;
    case EnemyState::IsHit:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 64;
      dest_rect.y = collision_box_.y - camera_y_ - 80;
      break;
    case EnemyState::IsDead:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 64;
      dest_rect.y = collision_box_.y - camera_y_ - 128;
      break;
    default:
      break;
  }

  if (flip_ == SDL_FLIP_NONE)
  {
    dest_rect.x = collision_box_.x - camera_x_ -96;
  }
  else
  {
    dest_rect.x = collision_box_.x - camera_x_ -32;
  }
  SDL_RenderCopyExF(renderer_, sprite_, &src_rect, &dest_rect, 0, nullptr, flip_);


  SDL_FRect adjusted_health_bar_border = {
    health_bar_border_.x - camera_x_,
    health_bar_border_.y - camera_y_,
    health_bar_border_.w,
    health_bar_border_.h
  };

  SDL_FRect adjusted_health_bar = {
    health_bar_.x - camera_x_,
    health_bar_.y - camera_y_,
    health_bar_.w,
    health_bar_.h
  };

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRectF(renderer_, &adjusted_health_bar_border);
  SDL_RenderDrawRectF(renderer_, &adjusted_health_bar_border);

  SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
  SDL_RenderFillRectF(renderer_, &adjusted_health_bar);
  SDL_RenderDrawRectF(renderer_, &adjusted_health_bar);
}