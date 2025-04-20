#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

enum class PlayerState 
{
  Standing = 0,
  Jumping = 4,
  WalkLeft = 2,
  WalkRight = 3,
  AttackMouseLeft = 14
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
    // I do this because I want to ensure you can only start another swing(attack) when the previous animation finished
    bool is_attacking_ = false;
    int world_x_;

    std::unordered_map<PlayerState, int> frame_counts_;
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
    Player(Window &window);
    void update();
    void render();
    void animate();
    void handleInput(const SDL_Event &event);
};

#endif