#include "game_scene.hpp"

GameScene::GameScene(Window &window, GameState &game_state)
: renderer_(window.getRenderer()), game_state_(game_state), player_(window, floor_rect_)
{
  int screen_width = window.getScreenWidth();
  int screen_height = window.getScreenHeight();
  int floor_width = screen_width;
  int floor_height = screen_height / 6;

  floor_rect_.x = 0;
  floor_rect_.y = screen_height - floor_height;
  floor_rect_.w = floor_width;
  floor_rect_.h = floor_height;

  background_rect_.x = 0;
  background_rect_.y = 0;
  background_rect_.w = screen_width;
  background_rect_.h = screen_height;
}

void GameScene::render()
{
  SDL_ShowCursor(SDL_DISABLE);

  SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255);
  SDL_RenderFillRect(renderer_, &background_rect_);
  SDL_RenderDrawRect(renderer_, &background_rect_);

  SDL_SetRenderDrawColor(renderer_, 34, 139, 34, 255);
  SDL_RenderFillRect(renderer_, &floor_rect_);
  SDL_RenderDrawRect(renderer_, &floor_rect_);

  player_.render();
}

void GameScene::handleEvent(const SDL_Event& event) 
{
  player_.handleInput(event);
}

void GameScene::update() 
{
  player_.update();
}