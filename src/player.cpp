#include "player.hpp"

Player::Player(Window &window) 
  : renderer_(window.getRenderer()),
    velocity_x_(0),
    velocity_y_(0),
    gravity_(1),
    jump_strength_(-18),
    is_jumping_(false),
    frame_width_(64),
    frame_height_(64),
    current_frame_(0), 
    animation_timer_(0),
    animation_speed_(16),
    is_attacking_(false)
{
  screen_height_ = window.getScreenHeight();
  screen_width_ = window.getScreenWidth();

  collision_box_.x = frame_width_;
  collision_box_.y = frame_height_;

  world_position_.x = 0;
  world_position_.y = screen_height_ - frame_height_ - (screen_height_ / 6);

  collision_box_.w = frame_width_;
  collision_box_.h = frame_height_;
  collision_box_.x = world_position_.x;
  collision_box_.y = world_position_.y;

  SDL_Surface *surface = IMG_Load("assets/WarriorMan-Sheet.png");
  sprite_sheet_ = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  frame_counts_[PlayerState::Standing] = 8;
  frame_counts_[PlayerState::WalkRight] = 8;
  frame_counts_[PlayerState::WalkLeft] = 8;
  frame_counts_[PlayerState::Jumping] = 11;
  frame_counts_[PlayerState::AttackMouseLeft] = 5;
}

void Player::handleInput(const SDL_Event &event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_SPACE && !is_jumping_)
    {
      velocity_y_ = jump_strength_;
      is_jumping_ = true;
    }
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
  {
    is_attacking_ = true;
  }
}

void Player::setTiles(const std::vector<Tile> *tiles)
{
  tiles_ = tiles;
}

void Player::animate()
{
  animation_timer_++;
  if (animation_timer_ >= animation_speed_)
  {
    int max_frames = frame_counts_[animation_state_];
    current_frame_++;

    if (animation_state_ == PlayerState::AttackMouseLeft && current_frame_ >= max_frames)
    {
      is_attacking_ = false;
      current_frame_ = 0;
      animation_state_ = PlayerState::Standing;
    }
    else
    {
      current_frame_ %= max_frames;
    }

    animation_timer_ = 0;
  }
}

void Player::setPlayerPosition(int position_x, int position_y)
{
  world_position_.x = position_x;
  world_position_.y = position_y;

  collision_box_.x = position_x;
  collision_box_.y = position_y;
}

void Player::update()
{
  const Uint8* keystate = SDL_GetKeyboardState(NULL);

  // --- Input ---
  if (is_attacking_)
  {
    animation_state_ = PlayerState::AttackMouseLeft;
    animate();
  }
  else if (keystate[SDL_SCANCODE_D])
  {
    velocity_x_ = 5;
    animation_state_ = PlayerState::WalkRight;
    animate();
  }
  else if (keystate[SDL_SCANCODE_A])
  {
    velocity_x_ = -5;
    animation_state_ = PlayerState::WalkLeft;
    animate();
  }
  else if (is_jumping_)
  {
    animation_state_ = PlayerState::Jumping;
    animate();
  }
  else
  {
    velocity_x_ = 0;
    animation_state_ = PlayerState::Standing;
    animate();
  }

  velocity_y_ += gravity_;

  SDL_Rect future_position_x = {
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

      SDL_Rect tile_rect = tile.destRect;

      if (SDL_HasIntersection(&future_position_x, &tile_rect))
      {
        if (velocity_x_ > 0)
          future_position_x.x = tile_rect.x - future_position_x.w;
        else if (velocity_x_ < 0)
          future_position_x.x = tile_rect.x + tile_rect.w;

        velocity_x_ = 0;
      }
    }
  }

  world_position_.x = future_position_x.x;

  // --- Vertical Movement ---
  SDL_Rect future_position_y = {
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

      SDL_Rect tile_rect = tile.destRect;

      if (SDL_HasIntersection(&future_position_y, &tile_rect))
      {
        if (velocity_y_ > 0)
        {
          // landing on top
          future_position_y.y = tile_rect.y - future_position_y.h;
          is_jumping_ = false;
        }
        else if (velocity_y_ < 0)
        {
          // hitting head
          future_position_y.y = tile_rect.y + tile_rect.h;
        }

        velocity_y_ = 0;
      }
    }
  }

  collision_box_.x = future_position_x.x;
  collision_box_.y = future_position_y.y;

  world_position_.x = collision_box_.x;
  world_position_.y = collision_box_.y;
}

SDL_Rect Player::getCollisionBox() const 
{
  return collision_box_;
}

void Player::render()
{
  const int scale = 3;

  SDL_Rect src_rect;
  src_rect.x = current_frame_ * (frame_width_ + 16);
  src_rect.y = static_cast<int>(animation_state_) * frame_height_;
  src_rect.w = frame_width_;
  src_rect.h = frame_height_;

  SDL_Rect dest_rect;
  dest_rect.x = world_position_.x - camera_x_ - 96;
  dest_rect.y = world_position_.y - camera_y_ - 80;
  dest_rect.w = frame_width_* scale;
  dest_rect.h = frame_height_ * scale;

  SDL_RenderCopy(renderer_, sprite_sheet_, &src_rect, &dest_rect);
}