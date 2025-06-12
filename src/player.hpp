#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include "level_builder.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "gear/weapon.hpp"
#include "gear/armor.hpp"

enum class PlayerState 
{
  Idle = 0,
  Jumping = 1,
  Walk = 2,
  AttackLMB = 3
};

enum class WeaponState
{
  NoItem = 0,
  DefaultSword = 1,
  SamuraiSword = 2
};

enum class ArmorState
{
  NoArmor = 0
};

class Player
{
  private:
    SDL_Renderer *renderer_;

    SDL_FPoint world_position_;
    SDL_FPoint render_size_;
    SDL_FRect collision_box_;
    //SDL_FRect attacking_collision_box;
    std::array<SDL_FRect, MAX_PLAYER_ATTACKS> attack_collision_boxes_;
    SDL_RendererFlip flip_;
    float velocity_x_ = 0.0f;
    float velocity_y_ = 0.0f;
    const float player_speed = 400.0f;
    float gravity_;
    int jump_strength_ = -20;
    bool is_jumping_ = false;
    float camera_x_ = 0.0f;
    float camera_y_ = 0.0f;
    float move_x_; 
    bool weapon_switched_ = false;
    WeaponState weapon_;
    ArmorState armor_;
    std::unique_ptr<Weapon> current_weapon_;

    int attack_collisionbox_offset = 64;

    const float fall_multiplier_ = 2.5f;
    const float low_jump_multiplier_ = 3.0f;
    
    SDL_Texture *sprite_sheet_;
    int frame_width_;
    int frame_height_;
    int animation_speed_;

    const std::vector<Tile> *tiles_;
    PlayerState animation_state_ = PlayerState::Idle;
    std::unordered_map<PlayerState, int> frame_counts_;

    int screen_height_;
    int screen_width_;

  public:
    Player(Window &window);
    // Do not make a destructor here switching weapons will not work if you do!
    void update(float delta_time);
    void render();
    void animate(float delta_time);
    void handleInput(const SDL_Event &event);
    void setPlayerPosition(float position_x, float position_y);
    bool isPlayerAttacking();
    bool isPlayerAttackDone();
    
    SDL_FPoint getPlayerPosition() const 
    {
      return world_position_;
    }

    void equipWeapon(std::unique_ptr<Weapon> weapon);
    Weapon *getWeapon() const;
    void setTiles(const std::vector<Tile> *tiles);
    SDL_FRect getCollisionBox() const;
    std::array<SDL_FRect, MAX_PLAYER_ATTACKS> getAttackCollisionBox() const;

    void setCameraOffset(int cam_x, int cam_y)
    {
      camera_x_ = cam_x;
      camera_y_ = cam_y;
    }

    int getCameraOffsetX() const { return camera_x_; }
    int getCameraOffsetY() const { return camera_y_; }
};

#endif
