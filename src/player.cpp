#include "player.hpp"
#include <string>
#include <iostream>
#include "gear/weapons/swords/default_sword.hpp"

Player::Player(Window &window) 
  : renderer_(window.getRenderer()),
    velocity_x_(0),
    velocity_y_(0),
    gravity_(750.0f),
    jump_strength_(-550),
    is_jumping_(false),
    frame_width_(64),
    frame_height_(64),
    current_frame_(0), 
    animation_timer_(0.0f),
    animation_speed_(100),
    is_attacking_(false)
{
  screen_height_ = window.getScreenHeight();
  screen_width_ = window.getScreenWidth();
  flip_ = SDL_FLIP_NONE;
  attack_animation_done_ = true;

  collision_box_.x = 64.0f;
  collision_box_.y = 64.0f;

  move_x_ = 0.0f;

  world_position_.x = 0.0f;
  world_position_.y = screen_height_ - frame_height_ - (screen_height_ / 6);

  collision_box_.w = frame_width_;
  collision_box_.h = frame_height_;
  collision_box_.x = world_position_.x;
  collision_box_.y = world_position_.y;

  SDL_Surface *surface = IMG_Load("assets/WarriorMan-Sheet.png");
  sprite_sheet_ = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  current_weapon_ = std::make_unique<DefaultSword>(renderer_);
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
    if (attack_animation_done_)
    {
      is_attacking_ = true;
      attack_animation_done_ = false;
      animation_state_ = PlayerState::AttackLMB;                             
      current_frame_ = 0;
      animation_timer_ = 0.0f;
    }
  }
}

void Player::setTiles(const std::vector<Tile> *tiles)
{
  tiles_ = tiles;
}

void Player::animate(float delta_time)
{
  attack_animation_done_ = current_weapon_->animate(delta_time, animation_state_);
}

void Player::setPlayerPosition(float position_x, float position_y)
{
  world_position_.x = position_x;
  world_position_.y = position_y;

  collision_box_.x = position_x;
  collision_box_.y = position_y;
}

void Player::update(float delta_time)
{
  const Uint8* keystate = SDL_GetKeyboardState(NULL);

  if (is_attacking_)
  {
    animation_state_ = PlayerState::AttackLMB;
    velocity_x_ = 0;
    move_x_ = 0;
    animate(delta_time);
  }
  else if (keystate[SDL_SCANCODE_D])
  {
    flip_ = SDL_FLIP_NONE;
    velocity_x_ = player_speed;
    move_x_ = velocity_x_ * delta_time;
    animation_state_ = PlayerState::Walk;
    animate(delta_time);
  }
  else if (keystate[SDL_SCANCODE_A])
  {
    flip_ = SDL_FLIP_HORIZONTAL;
    velocity_x_ = -player_speed;
    move_x_ = velocity_x_ * delta_time;
    animation_state_ = PlayerState::Walk;
    animate(delta_time);
  }
  else if (is_jumping_)
  {
    animation_state_ = PlayerState::Jumping;
    animate(delta_time);
  }
  else
  {
    velocity_x_ = 0;
    move_x_ = 0;
    animation_state_ = PlayerState::Idle;
    animate(delta_time);
  }

  bool space_held = keystate[SDL_SCANCODE_SPACE];

  if (velocity_y_ > 0) 
  {
    velocity_y_ += gravity_ * fall_multiplier_ * delta_time;
  }
  else if (velocity_y_ < 0 && !space_held) 
  {
    velocity_y_ += gravity_ * low_jump_multiplier_ * delta_time;
  }
  else 
  {
    velocity_y_ += gravity_ * delta_time;
  }

  float move_y = velocity_y_ * delta_time;

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
        if (move_x_ >= 0)
        {
          future_position_x.x = tile_rect.x - future_position_x.w;
        }
        else if (move_x_ < 0)
        {
          future_position_x.x = tile_rect.x + tile_rect.w;
        }

        velocity_x_ = 0;
        move_x_ = 0;
      }
    }
  }
  
  SDL_FRect future_position_y = {
    collision_box_.x,
    collision_box_.y + move_y,
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
        if (move_y >= 0)
        {
          future_position_y.y = tile_rect.y - future_position_y.h;
          is_jumping_ = false;
        }
        else if (move_y < 0)
        {
          future_position_y.y = tile_rect.y + tile_rect.h;
        }

        velocity_y_ = 0;
        move_y = 0;
      }
    }
  }

  collision_box_.x = future_position_x.x;
  collision_box_.y = future_position_y.y;

  world_position_.x = collision_box_.x;
  world_position_.y = collision_box_.y;

  float attack_offset = 0.0f;
  //The values are based on looking at how far the player swings his sword
  if (is_attacking_)
  {
    attack_offset = (flip_ == SDL_FLIP_NONE) ? 60.0f : -38.0f;
  }

  const float cam_smooth = 0.1f;

  camera_x_ += (world_position_.x - camera_x_ - screen_width_ / 2.0f) * cam_smooth;
  camera_y_ += (world_position_.y - camera_y_ - screen_height_ / 2.0f) * cam_smooth;

  //std::cout << "Move X: " << move_x_ << " | Pos X: " << world_position_.x << std::endl;
}

SDL_FRect Player::getCollisionBox() const 
{
  return collision_box_;
}

std::array<SDL_FRect, MAX_PLAYER_ATTACKS> Player::getAttackCollisionBox() const
{
  return attack_collision_boxes_; 
}

void Player::render()
{
  current_weapon_->render(flip_);
}
