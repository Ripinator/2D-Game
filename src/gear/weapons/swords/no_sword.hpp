#ifndef NO_SWORD_HPP
#define NO_SWORD_HPP

#include "gear/weapon.hpp"
#include "player.hpp"

enum class AnimationStateNoSword
{
  Idle = 0,
  Walk = 2,
  Jump = 4,
  AttackLMB = 8
};

class NO_SWORD : public Weapon
{
  private:
    std::array<SDL_FRect, 1> attack_hitboxes_;
    std::unordered_map<AnimationStateNoSword, int> frame_counts_;
    AnimationStateNoSword animation_state_ = AnimationStateNoSword::Idle;

  public:
    NO_SWORD(SDL_Renderer *renderer);
    ~NO_SWORD() = default;
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
    AnimationStateNoSword assignAnimationState(PlayerState animation_state);
};

#endif