#ifndef NIGHT_BORNE_HPP
#define NIGHT_BORNE_HPP

// This awesome asset is from here: 
// https://creativekind.itch.io/nightborne-warrior

#include "enemies.hpp"

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
    std::unordered_map<EnemyState, int> frame_counts_;

  public:
    NightBorne(Window &window, const SDL_Rect &floor_rect);

    void update() override;

    void render() override;
};

#endif