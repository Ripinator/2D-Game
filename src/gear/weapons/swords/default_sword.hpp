#ifndef DEFAULT_SWORD_HPP
#define DEFAULT_SWORD_HPP

#include "gear/weapon.hpp"

#define NUM_ATTACKS 8

enum class AnimationStateFrames
{
  Idle = 8,
  Walk = 8,
  Jump = 5,
  AttackLMB = 14
};

class DefaultSword : public Weapon
{
  private:
    std::array<SDL_FRect, NUM_ATTACKS> attack_hitboxes_;
    std::unordered_map<AnimationStateFrames, int> frame_counts_;
    AnimationState animation_state_ = AnimationState::Idle;

  public:
    DefaultSword(SDL_Renderer *renderer);
    SDL_FRect getAttackCollisionBox() const override;
    void attack() override;
    void render(SDL_RendererFlip flip) override;
    void update(float delta_time) override;
    void animate(float delta_time, std::any AnimationState) override;
    AnimationStateFrames assignAnimationState(AnimationState animation_state);
};

#endif