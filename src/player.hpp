#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include "level_builder.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

enum class PlayerState 
{
  Standing = 0,
  Jumping = 4,
  Walk = 3,
  AttackMouseLeft = 14
};

class Player
{
  private:
    SDL_Renderer *renderer_;

    SDL_FPoint world_position_;
    SDL_FPoint render_size_;
    SDL_FRect collision_box_;
    SDL_RendererFlip flip_;
    float velocity_x_ = 0.0f;
    float velocity_y_ = 0.0f;
    const float player_speed = 400.0f;
    float gravity_;
    int jump_strength_ = -20;
    bool is_jumping_ = false;
    // I do this because I want to ensure you can only start another swing(attack) when the previous animation finished
    bool is_attacking_ = false;
    float camera_x_ = 0.0f;
    float camera_y_ = 0.0f;
    float move_x_; 

    const float fall_multiplier_ = 2.5f;
    const float low_jump_multiplier_ = 3.0f;
    
    SDL_Texture *sprite_sheet_;
    int frame_width_;
    int frame_height_;
    int current_frame_;
    float animation_timer_;
    int animation_speed_;
    bool attack_animation_done_;

    const std::vector<Tile> *tiles_;
    PlayerState animation_state_ = PlayerState::Standing;
    std::unordered_map<PlayerState, int> frame_counts_;

    int screen_height_;
    int screen_width_;

  public:
    Player(Window &window);
    void update(float delta_time);
    void render();
    void animate(float delta_time);
    void handleInput(const SDL_Event &event);
    void setPlayerPosition(float position_x, float position_y);
    
    SDL_FPoint getPlayerPosition() const 
    {
      return world_position_;
    }

    void setTiles(const std::vector<Tile> *tiles);
    SDL_FRect getCollisionBox() const;

    void setCameraOffset(int cam_x, int cam_y)
    {
      camera_x_ = cam_x;
      camera_y_ = cam_y;
    }

    int getCameraOffsetX() const { return camera_x_; }
    int getCameraOffsetY() const { return camera_y_; }
};

#endif