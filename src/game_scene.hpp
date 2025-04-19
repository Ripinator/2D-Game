#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "player.hpp"
#include "enemies.hpp"
#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <memory>
#include <SDL2/SDL_ttf.h>
#include <vector>

class GameScene : public Scene
{
  private:
    SDL_Renderer *renderer_;
    GameState &game_state_;
    SDL_Rect background_rect_;
    SDL_Rect floor_rect_;
    Player player_;
    std::vector<std::unique_ptr<Enemy>> enemies_;

  public:
    GameScene(Window &window, GameState &game_state);
    void render() override;
    void update() override;
    void handleEvent(const SDL_Event& event) override;
};

#endif
