#include "mr_professor_wurst.hpp"

MrProfessorWurst::MrProfessorWurst(Window &window, int x, int y, const SDL_Rect &floor_rect)
: Enemy(window, floor_rect)
{
  frame_width_ = 32;
  frame_height_ = 32;
  velocity_x_ = 0;
  velocity_y_ = 0;
  health_ = 0;
  damage_ = 0;
  speed_ = 0;
  sprite_surface_ = IMG_Load("assets/enemies/MrProfessorWurst.png");
  is_attacking_ = false;
  is_falling_ = false;
  animation_speed_ = 25;
  animation_timer_ = 0;
  flip_ = SDL_FLIP_NONE;

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

  frame_counts_[EnemyStateMrProfessorWurst::Idle] = 8;
}

void MrProfessorWurst::setTiles(std::vector<Tile> *tiles)
{
  tiles_ = tiles;
}

void MrProfessorWurst::animate()
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

void MrProfessorWurst::setEnemyPosition(int position_x, int position_y)
{
  collision_box_.x = position_x;
  collision_box_.y = position_y;
}

void MrProfessorWurst::update(const SDL_FRect &player_box, const std::array<SDL_FRect, MAX_PLAYER_ATTACKS> &player_attacks_hitboxes, float delta_time)
{
  if (is_attacking_)
  {
    animation_state_ = EnemyStateMrProfessorWurst::Attack;
    animate();
  }
  else
  {
    velocity_x_ = 0;
    animation_state_ = EnemyStateMrProfessorWurst::Idle;
    // Iam doing this to make the animation flip more fluently
    if (player_box.x - collision_box_.x < 48)
    {
      flip_ = SDL_FLIP_NONE;
    }
    else
    {
      flip_ = SDL_FLIP_HORIZONTAL;
    }
    animate();
  }

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

void MrProfessorWurst::setCameraOffset(int x, int y)
{
  camera_x_ = x;
  camera_y_ = y;
}

void MrProfessorWurst::render()
{
  SDL_Rect src_rect;
  src_rect.x = current_frame_ * (frame_width_);
  src_rect.y = static_cast<int>(animation_state_) * frame_height_;
  src_rect.w = frame_width_;
  src_rect.h = frame_height_;

  SDL_FRect dest_rect;
  dest_rect.y = collision_box_.y - camera_y_;
  dest_rect.w = frame_width_* 3;
  dest_rect.h = frame_height_ * 3;

  if (flip_ == SDL_FLIP_NONE)
  {
    dest_rect.x = collision_box_.x - camera_x_;
  }
  else
  {
    dest_rect.x = collision_box_.x - camera_x_ -32;
  }

  SDL_RenderCopyExF(renderer_, sprite_, &src_rect, &dest_rect, 0, nullptr, flip_);
}