#include "game_scene.hpp"
#include <SDL2/SDL_image.h>
#include "game.hpp"

GameScene::GameScene(Window &window, GameState &game_state)
: renderer_(window.getRenderer()), game_state_(game_state), player_(window)
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();

  LevelBuilder builder(window, screen_width_, screen_height_, {});
  level_data_ = builder.loadLevel(1);
  player_.setTiles(&level_data_.tiles);

  player_.setPlayerPosition(level_data_.playerSpawn.x, level_data_.playerSpawn.y);
}

void GameScene::render()
{
  SDL_ShowCursor(SDL_DISABLE);

  SDL_Point player_position = player_.getPlayerPosition();
  
  int camera_x = player_position.x - (screen_width_ / 2 - 64 * 3 / 2);
  int camera_y = player_position.y - (screen_height_ * 3 / 4 - 64 * 3 / 2);

  player_.setCameraOffset(camera_x, camera_y);

  for (auto &background : level_data_.backgrounds) 
  {
    renderScaleTexture(renderer_, background, screen_width_, screen_height_);
  }

  for (auto &tile : level_data_.tiles)
  {
    SDL_Rect world_rect = tile.destRect;
    world_rect.x -= camera_x;
    world_rect.y -= camera_y;
    SDL_RenderCopy(renderer_, tile.texture, nullptr, &world_rect);
  }

  // You can draw the hitbox for debugging with the following

  // SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255); // Red
  // SDL_Rect player_box = player_.getCollisionBox();
  // player_box.x -= player_.getCameraOffsetX();
  // player_box.y -= player_.getCameraOffsetY();
  // SDL_RenderDrawRect(renderer_, &player_box);

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