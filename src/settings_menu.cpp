#include "settings_menu.hpp"

SettingsMenu::SettingsMenu(Window &window, TTF_Font *header_font, GameState &game_state)
: renderer_(window.getRenderer()), header_font_(header_font), game_state_(game_state)
{
  int screen_width = window.getScreenWidth();
  int screen_height = window.getScreenHeight();
  int rect_width = 800;
  int rect_height = 500;

  menu_rect_.x = (screen_width - rect_width) / 2;
  menu_rect_.y = (screen_height - rect_height) / 2;
  menu_rect_.w = rect_width;
  menu_rect_.h = rect_height;

  border_rect_.x = menu_rect_.x - 4;
  border_rect_.y = menu_rect_.y - 4;
  border_rect_.w = rect_width + 8;
  border_rect_.h = rect_height + 8;
}

SDL_Texture* SettingsMenu::createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect)
{
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  outRect.w = surface->w;
  outRect.h = surface->h;
  SDL_FreeSurface(surface);
  return texture;
}

void SettingsMenu::handleEvent(const SDL_Event &event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
      game_state_ = GameState::Menu;
    }
  }
}

void SettingsMenu::update()
{
  
}

void SettingsMenu::render()
{
  SDL_ShowCursor(SDL_ENABLE);
  
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  SDL_Point mouse_point = {mouse_x, mouse_y};
  SDL_Event event;

  SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255);
  SDL_RenderClear(renderer_);

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &border_rect_);
  SDL_RenderDrawRect(renderer_, &border_rect_);

  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
  SDL_RenderFillRect(renderer_, &menu_rect_);
  SDL_RenderDrawRect(renderer_, &menu_rect_);

  SDL_Color white = {255, 255, 255, 255};
  SDL_Texture *text_texture_header = createText("Settings", header_font_, white, text_header_rect_);
  text_header_rect_.x = menu_rect_.x + (menu_rect_.w - text_header_rect_.w) / 2;
  text_header_rect_.y = menu_rect_.y + 40;
  SDL_RenderCopy(renderer_, text_texture_header, nullptr, &text_header_rect_);
  SDL_DestroyTexture(text_texture_header);
}