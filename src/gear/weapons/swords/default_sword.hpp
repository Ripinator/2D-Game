#ifndef DEFAULT_SWORD_HPP
#define DEFAULT_SWORD_HPP

#include "gear/weapon.hpp"
#include "player.hpp"

#define NUM_ATTACKS 8

enum class AnimationStateFrames
{
  Idle = 0,
  Walk = 3,
  Jump = 4,
  AttackLMB = 14
};

class DefaultSword : public Weapon
{
  private:
    std::array<SDL_FRect, NUM_ATTACKS> attack_hitboxes_;
    std::unordered_map<AnimationStateFrames, int> frame_counts_;
    AnimationStateFrames animation_state_ = AnimationStateFrames::Idle;

  public:
    DefaultSword(SDL_Renderer *renderer);
    SDL_FRect getAttackCollisionBox() const override;
    bool get_animation_timer() override;
    void set_animation_timer(float animation_timer) override;
    bool get_current_frame() override;
    void set_current_frame(int current_frame) override;
    bool get_attack_animation_done() override;
    void set_attack_animation_done(bool attack_animation_done) override;
    bool get_attacking() override;
    void set_attacking(bool is_attacking) override;
    void render(SDL_RendererFlip flip) override;
    void update(float delta_time) override;
    void animate(float delta_time, std::any AnimationState) override;
    AnimationStateFrames assignAnimationState(PlayerState animation_state);
};

#endif