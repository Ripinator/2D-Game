#ifndef NIGHT_BORNE_HPP
#define NIGHT_BORNE_HPP

// This awesome asset is from here: 
// https://creativekind.itch.io/nightborne-warrior

#include "enemies/enemies.hpp"
#include "level_builder.hpp"

enum class EnemyState
{
  Idle = 0,
  Walking = 1,
  Attack = 2,
  IsHit = 3,
  IsDead = 4
};

class NightBorne : public Enemy
{
  private:
    SDL_FRect collision_box_;
    SDL_RendererFlip flip_;
    std::unordered_map<EnemyState, int> frame_counts_;
    std::vector<Tile> *tiles_;
    int frame_width_;
    int frame_height_;
    float velocity_x_;
    float velocity_y_;
    int current_frame_;
    int animation_timer_;
    int animation_speed_;
    bool is_attacking_ = false;
    bool is_falling_ = false;
    int camera_x_ = 0;
    int camera_y_ = 0;
    float move_x_;
    float move_y_;
    float wait;
    const float enemy_speed_ = 150.0f;
    EnemyState animation_state_ = EnemyState::Idle;

  public:
    NightBorne(Window &window, int x, int y, const SDL_Rect &floor_rect);

    void update(const SDL_FRect &player_box, float delta_time) override;
    void render() override;
    SDL_FRect getCollisionBox() override
    {
      return collision_box_;
    }
    void setCameraOffset(int x, int y) override;
    void animate(float delta_time);
    void setTiles(std::vector<Tile> *tiles) override;
    void setEnemyPosition(int position_x, int position_y) override;
};

#endif