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
  SDL_Surface *textSurface = TTF_RenderText_Blended(font_, "Sworld Lord", white);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);

  text_header_rect_.w = textSurface->w;
  text_header_rect_.h = textSurface->h;
  text_header_rect_.x = menu_rect_.x + (menu_rect_.w - text_header_rect_.w) / 2;
  text_header_rect_.y = menu_rect_.y + 40;


  SDL_RenderCopy(renderer_, textTexture, nullptr, &text_header_rect_);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(textTexture);
}
