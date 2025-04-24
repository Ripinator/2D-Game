#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

// Starting background: 
// https://free-game-assets.itch.io/ocean-and-clouds-free-pixel-art-backgrounds

#include "player.hpp"
#include "enemies/enemies.hpp"
#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include "utils/utils.hpp"
#include "level_builder.hpp"
#include <memory>
#include <SDL2/SDL_ttf.h>
#include <vector>

class GameScene : public Scene
{
  private:
    int screen_width_;
    int screen_height_;
    SDL_Renderer *renderer_;
    GameState &game_state_;
    SDL_Rect background_rect_;
    Player player_;
    LevelData level_data_;

    SDL_Texture* background_layer_1_texture_;
    SDL_Texture* background_layer_2_texture_;
    SDL_Texture* background_layer_3_texture_;
    SDL_Texture* background_layer_4_texture_;

  public:
    GameScene(Window &window, GameState &game_state);
    void render() override;
    void update(float delta_time) override;
    void handleEvent(const SDL_Event& event) override;
};

#endif
