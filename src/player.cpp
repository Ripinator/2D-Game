#include "player.hpp"

Player::Player(Window &window, const SDL_Rect &floor_rect) 
  : renderer_(window.getRenderer()),
    velocity_x_(0),
    velocity_y_(0),
    gravity_(1),
    jump_strength_(-20),
    is_jumping_(false),
    frame_width_(64),
    frame_height_(64),
    current_frame_(0), 
    frame_count_(8),
    animation_timer_(0),
    animation_speed_(16),
    floor_rect_(floor_rect)
{
  player_rect_.h = frame_width_ * 3;
  player_rect_.w = frame_height_ * 3;
  player_rect_.x = 700;
  player_rect_.y = window.getScreenHeight() - player_rect_.h - (window.getScreenHeight() / 6);

  screen_height = window.getScreenHeight();

  SDL_Surface *surface = IMG_Load("assets/WarriorMan-Sheet.png");
  sprite_sheet_ = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);
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
}

void Player::update()
{
  const Uint8* keystate = SDL_GetKeyboardState(NULL);

  if (keystate[SDL_SCANCODE_D])
  {
    velocity_x_ = 5;
    //animation_state_ = PlayerState::WalkRight;
  }
  else if (keystate[SDL_SCANCODE_A])
  {
    velocity_x_ = -5;
    //animation_state_ = PlayerState::WalkLeft;
  }
  else
  {
    velocity_x_ = 0;
    //animation_state_ = PlayerState::Standing;
  }

  if (is_jumping_)
  {
    //animation_state_ = PlayerState::Jumping;
  }
  
  player_rect_.x += velocity_x_;

  velocity_y_ += gravity_;
  player_rect_.y += velocity_y_;

  int floor_height = screen_height / 6;
  int ground_level = screen_height - floor_height;

  if (player_rect_.y + player_rect_.h >= ground_level)
  {
    player_rect_.y = ground_level - player_rect_.h;
    velocity_y_ = 0;
    is_jumping_ = false;
  }

  animation_timer_++;
  if (animation_timer_ >= animation_speed_)
  {
    current_frame_ = (current_frame_ + 1) % frame_count_;
    animation_timer_ = 0;
  }
}

void Player::render()
{
  SDL_Rect src_rect;
  src_rect.x = current_frame_ * (frame_width_ + 16);
  src_rect.y = 0;
  src_rect.w = frame_width_;
  src_rect.h = frame_height_;

  SDL_Rect dest_rect;
  dest_rect.x = player_rect_.x;
  dest_rect.y = player_rect_.y + 48;
  dest_rect.w = player_rect_.w;
  dest_rect.h = player_rect_.h;

  SDL_RenderCopy(renderer_, sprite_sheet_, &src_rect, &dest_rect);
}