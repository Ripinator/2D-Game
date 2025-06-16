#include "game_scene.hpp"
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <array>

GameScene::GameScene(Window &window, GameState &game_state, OverlayState &overlay_state)
: renderer_(window.getRenderer()), game_state_(game_state), player_(window, game_state_, overlay_state_), overlay_state_(overlay_state)
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();

  LevelBuilder builder(window, screen_width_, screen_height_, {});
  level_data_ = builder.loadLevel(1);
  player_.setTiles(&level_data_.tiles);

  for (size_t i = 0; i < level_data_.enemies.size(); ++i)
  {
    // Some debugging statements if you need it
    // SDL_Log("Enemy %zu: set at (%d, %d)", i, level_data_.enemy_spawn_[i].x, level_data_.enemy_spawn_[i].y);
    // SDL_Log("Total enemies: %zu", level_data_.enemies.size());
    if (i < level_data_.enemy_spawn_.size())
    {
      SDL_Point spawn = level_data_.enemy_spawn_[i];
      level_data_.enemies[i]->setTiles(&level_data_.tiles);
      level_data_.enemies[i]->setEnemyPosition(spawn.x, spawn.y);
    }
  }

  player_.setPlayerPosition(level_data_.playerSpawn.x, level_data_.playerSpawn.y);
}

void GameScene::render()
{
  SDL_ShowCursor(SDL_DISABLE);

  SDL_FPoint player_position = player_.getPlayerPosition();
  
  float camera_x = player_position.x - (screen_width_ / 2.0f - 64.0f * 3.0f / 2.0f);
  float camera_y = player_position.y - (screen_height_ * 3.0f / 4.0f - 64.0f * 3.0f / 2.0f);

  player_.setCameraOffset(camera_x, camera_y);

  for (auto &background : level_data_.backgrounds) 
  {
    renderScaleTexture(renderer_, background, screen_width_, screen_height_);
  }

  float rounded_camera_x = std::round(camera_x);
  float rounded_camera_y = std::round(camera_y);

  for (auto &tile : level_data_.tiles)
  {
    SDL_FRect world_rect = tile.destRect;
    world_rect.x -= rounded_camera_x;
    world_rect.y -= rounded_camera_y;
    SDL_RenderCopyF(renderer_, tile.texture, nullptr, &world_rect);
  }

  for (auto &enemy : level_data_.enemies)
  {
    enemy->setCameraOffset(camera_x, camera_y);
    enemy->render();

    // Debugging rect: this draws the hitbox

    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_FRect enemy_box = enemy->getCollisionBox();
    enemy_box.x -= camera_x;
    enemy_box.y -= camera_y;
    SDL_RenderDrawRectF(renderer_, &enemy_box);
  }

  // More hitbox rects

  SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255); // Red
  SDL_FRect player_box = player_.getCollisionBox();
  player_box.x -= player_.getCameraOffsetX();
  player_box.y -= player_.getCameraOffsetY();
  SDL_RenderDrawRectF(renderer_, &player_box);

  std::array<SDL_FRect, MAX_PLAYER_ATTACKS> player_attackrange_box = player_.getAttackCollisionBox();
  player_attackrange_box[0].x -= player_.getCameraOffsetX();
  player_attackrange_box[0].y -= player_.getCameraOffsetY();
  SDL_RenderDrawRectF(renderer_, &player_attackrange_box[0]);

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
    else if (event.key.keysym.sym == SDLK_i)
    {
      overlay_present_ = true;
      overlay_state_ = OverlayState::Inventory;  
    }
  }
}

void GameScene::update(float delta_time) 
{
  player_.update(delta_time); 

  auto& enemies = level_data_.enemies;
  auto it = enemies.begin();
  while (it != enemies.end())
  {
    (*it)->update(player_, player_.getCollisionBox(), player_.getAttackCollisionBox(), delta_time);
    if ((*it)->isDeadAndGone())
    {
      it = enemies.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
