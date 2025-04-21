#include "game_scene.hpp"
#include <SDL2/SDL_image.h>
#include "game.hpp"

GameScene::GameScene(Window &window, GameState &game_state)
: renderer_(window.getRenderer()), game_state_(game_state), player_(window)
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();

  LevelBuilder builder(window, screen_width_, screen_height_, {/* floor_rect_ or dummy if unused */});
  level_data_ = builder.loadLevel(1);

  player_.setPlayerPosition(level_data_.playerSpawn.x, level_data_.playerSpawn.y);
}

void GameScene::render()
{
  SDL_ShowCursor(SDL_DISABLE);

  for (auto &background : level_data_.backgrounds) 
  {
    renderScaleTexture(renderer_, background, screen_width_, screen_height_);
  }

  player_.render();  
}

void GameScene::handleEvent(const SDL_Event& event) 
{
  player_.handleInput(event);
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
      game_state_ = GameState::Menu;
    }
  }
}

void GameScene::update() 
{
  player_.update();
}