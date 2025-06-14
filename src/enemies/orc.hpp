#include "enemies.hpp"
#include "level_builder.hpp"

enum class OrcEnemyState
{
  Idle = 0,
  Walking = 1,
  BasicAttack = 2,
  HeavyAttack = 3,
  IsHit = 4,
  isDead = 5
};


class Orc : public Enemy
{
  private:
    SDL_FRect collision_box_;
    SDL_RendererFlip flip_;
    std::unordered_map<OrcEnemyState, int> frame_counts_;
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
    const float enemy_speed_ = 80.0f;
    float move_x_;
    float move_y_;
    float wait;
    float health_bar_full_size_;
    OrcEnemyState animation_state_ = OrcEnemyState::Idle;


    public:
      Orc(Window &window, int x, int y, const SDL_Rect &floor_rect);
      ~Orc();

      void update(Player &player, const SDL_FRect &player_box, const std::array<SDL_FRect, MAX_PLAYER_ATTACKS> &player_attack_hitboxes, float delta_time) override;
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
