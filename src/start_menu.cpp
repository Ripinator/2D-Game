#include "start_menu.hpp"
#include <SDL2/SDL_ttf.h>
#include "window.hpp"

StartMenu::StartMenu(Window &window, TTF_Font* header_font, TTF_Font* font, gameState &game_state) 
: renderer_(window.getRenderer()), header_font_(header_font), font_(font), game_state_(game_state)
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

  start_rect_.w = rect_width / 5;
  start_rect_.h = rect_height / 12;
  start_rect_.x = menu_rect_.x + (menu_rect_.w - start_rect_.w) / 2;
  start_rect_.y = menu_rect_.y + (menu_rect_.h - start_rect_.h) / 2 - 50;
  
  quit_rect_.w = rect_width / 5;
  quit_rect_.h = rect_height / 12;
  quit_rect_.x = menu_rect_.x + (menu_rect_.w - quit_rect_.w) / 2;
  quit_rect_.y = menu_rect_.y + (menu_rect_.h - quit_rect_.h) / 2;
}

void StartMenu::handleEvent(const SDL_Event& event) 
{
  
}

void StartMenu::update() 
{
  
}

void StartMenu::drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &textRect, bool hovered, const SDL_Event& e, gameState onClickState)
{
  if (hovered)
  {
    SDL_SetRenderDrawColor(renderer_, 200, 200, 200, 255);
  }
  else
  {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  }

  SDL_RenderFillRect(renderer_, &rect);
  SDL_RenderDrawRect(renderer_, &rect);
  SDL_RenderCopy(renderer_, texture, nullptr, &textRect);
}

SDL_Texture* StartMenu::createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect)
{
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  outRect.w = surface->w;
  outRect.h = surface->h;
  SDL_FreeSurface(surface);
  return texture;
}

void StartMenu::render() 
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL_Point mouse_point = {mouse_x, mouse_y};

    bool hovered_quit = SDL_PointInRect(&mouse_point, &quit_rect_);
    bool hovered_start = SDL_PointInRect(&mouse_point, &start_rect_);

    SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255);
    SDL_RenderClear(renderer_);

    SDL_SetRenderDrawColor(renderer_, 255, 165, 0, 255);
    SDL_RenderFillRect(renderer_, &border_rect_);
    SDL_RenderDrawRect(renderer_, &border_rect_);

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer_, &menu_rect_);
    SDL_RenderDrawRect(renderer_, &menu_rect_);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Texture* text_texture_header = createText("Sworld Lord", header_font_, white, text_header_rect_);
    text_header_rect_.x = menu_rect_.x + (menu_rect_.w - text_header_rect_.w) / 2;
    text_header_rect_.y = menu_rect_.y + 40;
    SDL_RenderCopy(renderer_, text_texture_header, nullptr, &text_header_rect_);
    SDL_DestroyTexture(text_texture_header);

    SDL_Color black = {0, 0, 0, 255};
    SDL_Texture* text_texture_start = createText("Start", font_, black, text_start_rect_);
    text_start_rect_.x = start_rect_.x + (start_rect_.w - text_start_rect_.w) / 2;
    text_start_rect_.y = start_rect_.y + (start_rect_.h - text_start_rect_.h) / 2;
    drawButton(start_rect_, text_texture_start, text_start_rect_, hovered_start);
    SDL_DestroyTexture(text_texture_start);

    SDL_Texture* text_texture_quit = createText("Quit", font_, black, text_quit_rect_);
    text_quit_rect_.x = quit_rect_.x + (quit_rect_.w - text_quit_rect_.w) / 2;
    text_quit_rect_.y = quit_rect_.y + (quit_rect_.h - text_quit_rect_.h) / 2;
    drawButton(quit_rect_, text_texture_quit, text_quit_rect_, hovered_quit);
    SDL_DestroyTexture(text_texture_quit);

    SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_SetCursor(cursor);
}
