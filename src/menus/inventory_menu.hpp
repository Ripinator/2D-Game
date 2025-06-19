#ifndef INVENTORY_MENU_HPP
#define INVENTORY_MENU_HPP

#include "overlay.hpp"
#include "game.hpp"
#include "window.hpp"
#include "inventory-system/inventory.hpp"
#include "inventory-system/item.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <array>

class InventoryMenu : public Overlay
{ 
  private:
    std::vector<Item> items_;
    Inventory inventory_;
    SDL_Renderer *renderer_;
    SDL_Rect src_inventory_menu_rect_;
    SDL_Rect dest_inventory_menu_rect_;
    TTF_Font *font_;
    OverlayState &overlay_state_;
    GameState &game_state_;
    SDL_Event event_;
    SDL_Rect border_rect_;
    SDL_Surface *player_inventory_surface_;
    SDL_Texture *player_inventory_texture_;
    std::array<std::array<SDL_Rect, 8>, 4> inventory_slot_rects_;
    int screen_width_;
    int screen_height_;

    const int INVENTORY_SIZE = 32;
    const int INVENTORY_ROWS = 4;
    const int INVENTORY_COLUMNS = 8;
    const int SLOT_WIDTH = 64;
    const int SLOT_HEIGHT = 64;
    const int SLOT_SPACING = 10;

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
