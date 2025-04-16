#ifndef START_MENU_HPP
#define START_MENU_HPP

#include "scene.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>

class StartMenu : public Scene 
{
  private:
    SDL_Renderer* renderer_;
    SDL_Rect menu_rect_;
    SDL_Rect quit_rect_;
    SDL_Rect start_rect_;
    SDL_Rect border_rect_;
    SDL_Rect text_header_rect_;
    SDL_Rect text_quit_rect_;
    SDL_Rect text_start_rect_;
    TTF_Font* header_font_;
    TTF_Font* font_;

  public:
    StartMenu(Window& window, TTF_Font* header_font, TTF_Font* font);
    void handleEvent(const SDL_Event& event) override;
    void update() override;
    void render() override;
};

#endif
