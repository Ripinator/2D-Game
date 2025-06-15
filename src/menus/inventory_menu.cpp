#include "inventory_menu.hpp"

InventoryMenu::InventoryMenu(Window &window, TTF_Font *font, OverlayState &overlay_state, GameState &game_state)
: renderer_(window.getRenderer()), font_(font), overlay_state_(overlay_state), game_state_(game_state) 
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();

  inventory_menu_rect_.x = screen_width_ / 2;
  inventory_menu_rect_.y = screen_height_ / 2;
  inventory_menu_rect_.w = screen_width_ / 7;
  inventory_menu_rect_.h = screen_height_ / 7;

  border_rect_.x = inventory_menu_rect_.x + 8;
  border_rect_.y = inventory_menu_rect_.y + 8;
  border_rect_.w = screen_width_ - 8;
  border_rect_.h = screen_height_ - 8;
}

SDL_Texture *InventoryMenu::createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect)
{
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  if (!surface)
  {
    std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
    outRect.w = outRect.h = 0;
    return nullptr;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  outRect.w = surface->w;
  outRect.h = surface->h;
  SDL_FreeSurface(surface);
  return texture;
}

void InventoryMenu::handleEvent(const SDL_Event &event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_i)
    {
      overlay_state_ = OverlayState::None;
    }
  }
}

void InventoryMenu::update(float delta_time) 
{
  
}

void InventoryMenu::render()
{
  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
  SDL_RenderFillRect(renderer_, &inventory_menu_rect_);
  SDL_RenderDrawRect(renderer_, &inventory_menu_rect_);

  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
  SDL_RenderFillRect(renderer_, &border_rect_);
  SDL_RenderDrawRect(renderer_, &border_rect_);
}
