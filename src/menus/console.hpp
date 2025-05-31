#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "SDL2/SDL_ttf.h"
#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <vector>

class Console : public Scene
{
  private:
    SDL_Renderer *renderer_;
    Window &window_;
    SDL_Event event;
    SDL_Rect console_rect_;
    TTF_Font *font_;
    GameState &game_state_;
    int width_;
    int height_;

  public:
    Console(Window &window, TTF_Font *font, GameState &game_state);
    void handleEvent(const SDL_Event &event) override;
    void update(float delta_time) override;
    void render() override;
};

#endif