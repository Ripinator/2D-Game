#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>

class GameScene : public Scene
{
  private:
    SDL_Renderer* renderer_;
    GameState &game_state_;
    SDL_Rect floor_rect_;

  public:
    GameScene(Window &window, GameState &game_state);
    void render() override;
    void update() override;
    void handleEvent(const SDL_Event& event) override;
};

#endif
