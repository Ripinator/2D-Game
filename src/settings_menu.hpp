#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>

class SettingsMenu : public Scene
{
  private:
    SDL_Renderer *renderer_;
    SDL_Rect menu_rect_;
    SDL_Rect border_rect_;
    SDL_Rect text_header_rect_;
    TTF_Font *header_font_;
    TTF_Font *font_;
    GameState &game_state_;
    SDL_Event event;

  public:
    SettingsMenu(Window &window, TTF_Font *header_font, GameState &game_state);
    void handleEvent(const SDL_Event &event) override;
    void update() override;
    void drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &text_rect, bool hovered, SDL_Event &event);
    SDL_Texture *createText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Rect& outRect);
    void render() override;
};

#endif