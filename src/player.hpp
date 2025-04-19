#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

enum class PlayerState 
{
  Standing,
  WalkRight,
  WalkLeft,
  Jumping
};

class Player
{
  private:
    SDL_Renderer *renderer_;
    SDL_Rect player_rect_;
    SDL_Rect floor_rect_;
    PlayerState animation_state_ = PlayerState::Standing;
    int velocity_x_ = 0;
    int velocity_y_ = 0;
    int gravity_ = 1;
    int jump_strength_ = -20;
    bool is_jumping_ = false;

    SDL_Rect standing_rect_;
    int frame_width_;
    int frame_height_;
    int current_frame_;
    int frame_count_;
    int animation_timer_;
    int animation_speed_;
    SDL_Texture *sprite_sheet_;

    int screen_height;

  public:
    Player(Window &window, const SDL_Rect &floor_rect);
    void update();
    void render();
    void handleInput(const SDL_Event &event);
};

#endif