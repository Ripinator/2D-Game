#include "player.hpp"

Player::Player(Window &window) : renderer_(window.getRenderer())
{
  player_rect_.h = 200;
  player_rect_.w = 50;
  player_rect_.x = 700;
  player_rect_.y = window.getScreenHeight() - player_rect_.h - (window.getScreenHeight() / 6);
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
  }
  else if (keystate[SDL_SCANCODE_A])
  {
    velocity_x_ = -5;
  }
  else
  {
    velocity_x_ = 0;
  }
      
  player_rect_.x += velocity_x_;

  velocity_y_ += gravity_;
  player_rect_.y += velocity_y_;

  int floor_y = renderer_ ? SDL_GetWindowSurface(SDL_GetWindowFromID(1))->h : 1080;
  int floor_height = floor_y / 6;
  int ground_level = floor_y - floor_height;

  if (player_rect_.y + player_rect_.h >= ground_level)
  {
    player_rect_.y = ground_level - player_rect_.h;
    velocity_y_ = 0;
    is_jumping_ = false;
  }
}

void Player::render()
{
  SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &player_rect_);
  SDL_RenderDrawRect(renderer_, &player_rect_);
}