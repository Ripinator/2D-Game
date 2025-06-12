#ifndef MR_PROFESSOR_WURST
#define MR_PROFESSOR_WURST

// This awesome asset is from kamodoo's head lets go

#include "enemies.hpp"
#include "level_builder.hpp"

#include "enemies.hpp"
#include "level_builder.hpp"

enum class EnemyStateMrProfessorWurst
{
  Idle = 0,
  Walk = 1,
  Attack = 2
};

class MrProfessorWurst : public Enemy
{
  private:
    SDL_FRect collision_box_;
    SDL_RendererFlip flip_;
    std::unordered_map<EnemyStateMrProfessorWurst, int> frame_counts_;
    std::vector<Tile> *tiles_;
    int frame_width_;
    int frame_height_;
    int velocity_x_;
    int velocity_y_;
    int current_frame_;
    int animation_timer_;
    int animation_speed_;
    bool is_attacking_ = false;
    bool is_falling_ = false;
    int camera_x_ = 0;
    int camera_y_ = 0;
    EnemyStateMrProfessorWurst animation_state_ = EnemyStateMrProfessorWurst::Idle;

  public:
    MrProfessorWurst(Window &window, int x, int y, const SDL_Rect &floor_rect);

    void update(Player &player, const SDL_FRect &player_box, const std::array<SDL_FRect, MAX_PLAYER_ATTACKS> &player_attacks_hitboxes, float delta_time) override;
    void render() override;
    SDL_FRect getCollisionBox() override
    {
      return collision_box_;
    }
    void setCameraOffset(int x, int y) override;
    void animate();
    void setTiles(std::vector<Tile> *tiles) override;
    void setEnemyPosition(int position_x, int position_y) override;
};

#endif
