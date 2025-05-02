#include "orc.hpp"

Orc::Orc(Window &window, int x, int y, const SDL_Rect &floor_rect)
: Enemy(window, floor_rect)
{
  frame_width_ = 64;
  frame_height_ = 64;
  velocity_x_ = 0;
  velocity_y_ = 0;
  health_ = 200;
  damage_ = 15;
  speed_ = 1;
  sprite_surface_ = IMG_Load("assets/enemies/Orc.png");
  is_attacking_ = false;
  is_falling_ = false;
  animation_speed_ = 20;
  animation_timer_ = 0;
  flip_ = SDL_FLIP_NONE;
  wait = 0;


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

  frame_counts_[OrcEnemyState::Idle] = 6;
  frame_counts_[OrcEnemyState::Walking] = 8;
  frame_counts_[OrcEnemyState::BasicAttack] = 6;
  frame_counts_[OrcEnemyState::HeavyAttack] = 6;
  frame_counts_[OrcEnemyState::IsHit] = 4;
  frame_counts_[OrcEnemyState::isDead] = 4;
}

void Orc::setTiles(std::vector<Tile> *tiles)
{
  tiles_ = tiles;
}

void Orc::animate()
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

void Orc::setEnemyPosition(int position_x, int position_y)
{
  collision_box_.x = position_x;
  collision_box_.y = position_y;
}

void Orc::update(const SDL_FRect &player_box, float delta_time)
{
   wait += delta_time;
  if (wait >= 1)
  {
    wait = 0;
  }

  const int detection_range = 200;
  int distance_to_player = player_box.x - collision_box_.x;

  if (std::abs(distance_to_player < detection_range))
  {
    animation_state_ = OrcEnemyState::Idle;
    velocity_x_ = 0;

    // This is nice but might not be so good for a smooth transition I dont know why i kept this at this point
    flip_ = (distance_to_player < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  }
  else
  {
    animation_state_ = OrcEnemyState::Walking;
    velocity_x_ -= 200;
  }

  animate();
  //  Horizontal movement
  SDL_FRect future_position_x = {
    collision_box_.x + velocity_x_,
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
      }
    }
  }

  // --- Vertical Movement ---
  SDL_FRect future_position_y = {
    collision_box_.x,
    collision_box_.y + velocity_y_,
    collision_box_.w,
    collision_box_.h
  };

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
      }
    }
  }


  collision_box_.x = future_position_x.x;
  collision_box_.y = future_position_y.y;
}

void Orc::setCameraOffset(int x, int y)
{
  camera_x_ = x;
  camera_y_ = y;
}

void Orc::render()
{
  SDL_Rect src_rect;
  src_rect.x = current_frame_ * (frame_width_ + 16);
  src_rect.w = frame_width_;
  src_rect.h = frame_height_;

  SDL_FRect dest_rect;
  dest_rect.w = frame_width_* 3;
  dest_rect.h = frame_height_ * 3;

  // there are some seemingly random hardcoded values in here because the spritesheet is weird and iam to lazy to change
  // also maybe a switch statement is not the optimale solution but i dont care just wanted to state this so i can cringe at this 
  // in a few years
  switch (animation_state_)
  {
    case OrcEnemyState::Idle:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_;
      dest_rect.y = collision_box_.y - camera_y_ - 110;
      break;
    case OrcEnemyState::Walking:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 32;
      dest_rect.y = collision_box_.y - camera_y_ - 80;
      break;
    case OrcEnemyState::BasicAttack:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 32;
      dest_rect.y = collision_box_.y - camera_y_ - 128;
      break;
    case OrcEnemyState::HeavyAttack:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 64;
      dest_rect.y = collision_box_.y - camera_y_ - 80;
      break;
    case OrcEnemyState::IsHit:
      src_rect.y = static_cast<int>(animation_state_) * frame_height_ + 64;
      dest_rect.y = collision_box_.y - camera_y_ - 128;
      break;
    case OrcEnemyState::isDead:
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
}