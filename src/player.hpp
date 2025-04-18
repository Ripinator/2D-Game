#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Player
{
  private:
    SDL_Renderer *renderer_;
    SDL_Rect player_rect_;
    int velocity_x_ = 0;
    int velocity_y_ = 0;
    int gravity_ = 1;
    int jump_strength_ = -20;
    bool is_jumping_ = false;

    int frame_width_;
    int frame_height_;
    int current_frame_;
    int frame_count_;
    int animation_timer_;
    int animation_speed_;
    SDL_Texture *sprite_sheet_;

  public:
    Player(Window &window);
    void update();
    void render();
    void handleInput(const SDL_Event &event);
};

#endif