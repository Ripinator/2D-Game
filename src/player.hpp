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
  WalkLeft = 2,
  WalkRight = 3,
  AttackMouseLeft = 14
};

class Player
{
  private:
    SDL_Renderer *renderer_;

    SDL_Point world_position_;
    SDL_Point render_size_;
    SDL_Rect collision_box_;
    int velocity_x_ = 0;
    int velocity_y_ = 0;
    int gravity_ = 1;
    int jump_strength_ = -20;
    bool is_jumping_ = false;
    // I do this because I want to ensure you can only start another swing(attack) when the previous animation finished
    bool is_attacking_ = false;
    int camera_x_ = 0;
    int camera_y_ = 0;
    
    
    SDL_Texture *sprite_sheet_;
    int frame_width_;
    int frame_height_;
    int current_frame_;
    int animation_timer_;
    int animation_speed_;

    const std::vector<Tile> *tiles_;
    PlayerState animation_state_ = PlayerState::Standing;
    std::unordered_map<PlayerState, int> frame_counts_;

    int screen_height_;
    int screen_width_;

  public:
    Player(Window &window);
    void update();
    void render();
    void animate();
    void handleInput(const SDL_Event &event);
    void setPlayerPosition(int position_x, int position_y);
    
    SDL_Point getPlayerPosition() const 
    {
      return world_position_;
    }

    void setTiles(const std::vector<Tile> *tiles);
    SDL_Rect getCollisionBox() const;

    void setCameraOffset(int cam_x, int cam_y)
    {
      camera_x_ = cam_x;
      camera_y_ = cam_y;
    }

    int getCameraOffsetX() const { return camera_x_; }
    int getCameraOffsetY() const { return camera_y_; }
};

#endif