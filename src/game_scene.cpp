#include "game_scene.hpp"
#include <SDL2/SDL_image.h>
#include "game.hpp"

GameScene::GameScene(Window &window, GameState &game_state)
: renderer_(window.getRenderer()), game_state_(game_state), player_(window)
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();
  int floor_width = screen_width_;
  int floor_height = screen_height_ / 6;

  SDL_Surface *background_layer_1 = IMG_Load("assets/level_1_background/1.png");
  SDL_Surface *background_layer_2 = IMG_Load("assets/level_1_background/2.png");
  SDL_Surface *background_layer_3 = IMG_Load("assets/level_1_background/3.png");
  SDL_Surface *background_layer_4 = IMG_Load("assets/level_1_background/4.png");

  background_layer_1_texture_ = SDL_CreateTextureFromSurface(renderer_, background_layer_1);
  background_layer_2_texture_ = SDL_CreateTextureFromSurface(renderer_, background_layer_2);
  background_layer_3_texture_ = SDL_CreateTextureFromSurface(renderer_, background_layer_3);
  background_layer_4_texture_ = SDL_CreateTextureFromSurface(renderer_, background_layer_4);

  SDL_FreeSurface(background_layer_1);
  SDL_FreeSurface(background_layer_2);
  SDL_FreeSurface(background_layer_3);
  SDL_FreeSurface(background_layer_4);

  player_ = Player(window);

  background_rect_.x = 0;
  background_rect_.y = 0;
  background_rect_.w = screen_width_;
  background_rect_.h = screen_height_;
}

void GameScene::render()
{
  SDL_ShowCursor(SDL_DISABLE);

  renderScaleTexture(renderer_, background_layer_1_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, background_layer_2_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, background_layer_3_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, background_layer_4_texture_, screen_width_, screen_height_);

  player_.render();

  // SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255);
  // SDL_RenderFillRect(renderer_, &background_rect_);
  // SDL_RenderDrawRect(renderer_, &background_rect_);

  // SDL_SetRenderDrawColor(renderer_, 34, 139, 34, 255);
  // SDL_RenderFillRect(renderer_, &floor_rect_);
  // SDL_RenderDrawRect(renderer_, &floor_rect_);
  
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