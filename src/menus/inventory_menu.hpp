#ifndef INVENTORY_MENU_HPP
#define INVENTORY_MENU_HPP

#include "overlay.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

class InventoryMenu : public Overlay
{ 
  private:
    SDL_Renderer *renderer_;
    SDL_Rect inventory_menu_rect_;
    TTF_Font *font_;
    OverlayState &overlay_state_;
    GameState &game_state_;
    SDL_Event event_;
    SDL_Rect border_rect_;
    int screen_width_;
    int screen_height_;

  public:
    InventoryMenu(Window &window, TTF_Font *font, OverlayState &overlay_state, GameState &game_state);
    ~InventoryMenu() = default;
    void handleEvent(const SDL_Event &event) override;
    SDL_Texture *createText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Rect& outRect);
    void update(float delta_time) override;
    void render() override;
    void setType(OverlayState overlay_state);
};

#endif
