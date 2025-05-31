#include "menus/console.hpp"

Console::Console(Window &window, TTF_Font *font, GameState &game_state)
  : renderer_(window.getRenderer()), font_(font), window_(window), game_state_(game_state)
{
  width_ = (window.getScreenWidth() / 3) * 2;
  height_ = (window.getScreenHeight() / 3) * 2;
}

void Console::handleEvent(const SDL_Event &event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
      game_state_ = GameState::Play;
    }
  }
}

void Console::update(float delta_time)
{

}

void Console::render()
{
  // SDL_ShowCursor(SDL_ENABLE);
  // SDL_Color black = {0, 0, 0, 255};

  // int mouse_x, mouse_y;
  // SDL_GetMouseState(&mouse_x, &mouse_y);
  // SDL_Point mouse_point = {mouse_x, mouse_y};

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &console_rect_);
  SDL_RenderDrawRect(renderer_, &console_rect_);
}