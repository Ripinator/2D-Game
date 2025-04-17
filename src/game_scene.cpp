#include "game_scene.hpp"

GameScene::GameScene(Window &window, GameState &game_state)
: renderer_(window.getRenderer()), game_state_(game_state)
{
  int screen_width = window.getScreenWidth();
  int screen_height = window.getScreenHeight();
  int floor_width = screen_width;
  int floor_height = screen_height / 6;

  floor_rect_.x = 0;
  floor_rect_.y = screen_width - floor_height;
  floor_rect_.w = floor_width;
  floor_rect_.h = floor_height;
}

void GameScene::render()
{
  SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255);
  SDL_RenderFillRect(renderer_, &floor_rect_);
  SDL_RenderDrawRect(renderer_, &floor_rect_);
}

void GameScene::handleEvent(const SDL_Event& event) 
{
  
}

void GameScene::update() 
{
  
}