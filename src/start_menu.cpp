#include "start_menu.hpp"
#include <SDL2/SDL_ttf.h>
#include "window.hpp"

StartMenu::StartMenu(Window &window, TTF_Font* header_font, TTF_Font* font) 
: renderer_(window.getRenderer()), header_font_(header_font), font_(font)
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

void StartMenu::render() 
{
  SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255);
  SDL_RenderClear(renderer_);
  
  // draw the border for the start menu
  SDL_SetRenderDrawColor(renderer_, 255, 165, 0, 255);
  SDL_RenderFillRect(renderer_, &border_rect_);
  SDL_RenderDrawRect(renderer_, &border_rect_);

  // draw the start menu
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &menu_rect_);
  SDL_RenderDrawRect(renderer_, &menu_rect_);

  // draw text for the start menu
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 255};
  SDL_Surface *textSurfaceFont = TTF_RenderText_Blended(header_font_, "Sworld Lord", white);
  SDL_Surface *textSurfaceHeaderFontQuit = TTF_RenderText_Blended(font_, "Quit", black);
  SDL_Surface *textSurfaceHeaderFontStart = TTF_RenderText_Blended(font_, "Start", black);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurfaceFont);
  SDL_Texture* textTextureStart = SDL_CreateTextureFromSurface(renderer_, textSurfaceHeaderFontStart);
  SDL_Texture* textTextureQuit = SDL_CreateTextureFromSurface(renderer_, textSurfaceHeaderFontQuit);

  text_header_rect_.w = textSurfaceFont->w;
  text_header_rect_.h = textSurfaceFont->h;
  text_header_rect_.x = menu_rect_.x + (menu_rect_.w - text_header_rect_.w) / 2;
  text_header_rect_.y = menu_rect_.y + 40;

  // draw start rect and text
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer_, &start_rect_);
  SDL_RenderDrawRect(renderer_, &start_rect_);

  text_start_rect_.w = textSurfaceHeaderFontStart->w;
  text_start_rect_.h = textSurfaceHeaderFontStart->h;
  text_start_rect_.x = menu_rect_.x + (menu_rect_.w - text_start_rect_.w) / 2;
  text_start_rect_.y = menu_rect_.y + 185;

  // draw the quit rect and text
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer_, &quit_rect_);
  SDL_RenderDrawRect(renderer_, &quit_rect_);

  text_quit_rect_.w = textSurfaceHeaderFontQuit->w;
  text_quit_rect_.h = textSurfaceHeaderFontQuit->h;
  text_quit_rect_.x = menu_rect_.x + (menu_rect_.w - text_quit_rect_.w) / 2;
  text_quit_rect_.y = menu_rect_.y + 235;

  // draw cursor
  SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
  SDL_SetCursor(cursor);

  SDL_RenderCopy(renderer_, textTexture, nullptr, &text_header_rect_);
  SDL_RenderCopy(renderer_, textTextureStart, nullptr, &text_start_rect_);
  SDL_RenderCopy(renderer_, textTextureQuit, nullptr, &text_quit_rect_);

  SDL_FreeSurface(textSurfaceFont);
  SDL_DestroyTexture(textTexture);
}
