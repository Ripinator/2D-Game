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

  render_size_.x = frame_width_ * 3;
  render_size_.y = frame_height_ * 3;

  world_position_.x = 0;
  world_position_.y = screen_height_ - render_size_.y - (screen_height_ / 6);

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
}

void Player::update()
{
  const Uint8* keystate = SDL_GetKeyboardState(NULL);

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
  
  world_position_.x += velocity_x_;
  velocity_y_ += gravity_;
  world_position_.y += velocity_y_;

  int floor_height = screen_height_ / 6;
  int ground_level = screen_height_ - floor_height;

  if (world_position_.y + render_size_.y >= ground_level)
  {
    world_position_.y = ground_level - render_size_.y;
    velocity_y_ = 0;
    is_jumping_ = false;
  }
}

void Player::render()
{
  SDL_Rect src_rect;
  src_rect.x = current_frame_ * (frame_width_ + 16);
  src_rect.y = static_cast<int>(animation_state_) * frame_height_;
  src_rect.w = frame_width_;
  src_rect.h = frame_height_;

  SDL_Rect dest_rect;
  dest_rect.x = screen_width_ / 2 - render_size_.x / 2;
  dest_rect.y = screen_height_ / 2 - render_size_.y / 2 + 48;
  dest_rect.w = render_size_.x;
  dest_rect.h = render_size_.y;

  SDL_RenderCopy(renderer_, sprite_sheet_, &src_rect, &dest_rect);
}