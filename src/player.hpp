#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>

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

  public:
    Player(Window &window);
    void update();
    void render();
    void handleInput(const SDL_Event &event);
};

#endif