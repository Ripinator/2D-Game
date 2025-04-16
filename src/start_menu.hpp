#ifndef START_MENU_HPP
#define START_MENU_HPP

#include "scene.hpp"
#include "game.hpp"
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
    gameState &game_state_;


  public:
    StartMenu(Window& window, TTF_Font* header_font, TTF_Font* font, gameState &game_state);
    void handleEvent(const SDL_Event& event) override;
    void update() override;
    void drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &text_rect, bool hovered, const SDL_Event& e, gameState on_click_state);
    SDL_Texture* createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect);
    void render() override;
};

#endif
