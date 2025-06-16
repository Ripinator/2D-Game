#ifndef SETTINGS_MENU_HPP
#define SETTINGS_MENU_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include "utils/utils.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

struct DropDownMenu
{
  std::string label;
  SDL_Rect rect;
  bool selected = false;
};

class SettingsMenu : public Scene
{
  private:
    int selected_display_;
    int number_of_displays_;
    int screen_width_;
    int screen_height_;
    bool dropdown_open_;
    bool overlay_active_;
    std::string display_name_;
    std::vector<DropDownMenu> display_options_;
    std::vector<DropDownMenu> resolution_options_;
    std::vector<std::string> displays_;
    SDL_Renderer *renderer_;
    SDL_Rect displays_rect_;
    SDL_Rect resolutions_rect_;
    SDL_Rect text_displays_rect_;
    SDL_Rect text_resolutions_rect_;
    SDL_Rect menu_rect_;
    SDL_Rect border_rect_;
    SDL_Rect text_header_rect_;
    TTF_Font *header_font_;
    TTF_Font *font_;
    GameState &game_state_;
    SDL_Event event;
    Window &window_;

    SDL_Texture *text_texture_displays_;
    SDL_Texture *text_texture_resolutions_;
    SDL_Texture *blue_background_texture_;
    SDL_Texture *white_clouds_texture_;
    SDL_Texture *blue_clouds_texture_;
    SDL_Texture *water_texture_;
    SDL_Texture *grass_1_texture_;
    SDL_Texture *grass_2_texture_;
    SDL_Texture *grass_3_texture_; 

  public:
    SettingsMenu(Window &window, TTF_Font *header_font, TTF_Font *font, GameState &game_state);
    void handleEvent(const SDL_Event &event) override;
    void update(float delta_time) override;
    void drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &text_rect, bool hovered, SDL_Event &event);
    SDL_Texture *createText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Rect &outRect);
    void render() override;
    bool OverlayPresent() override { return overlay_active_; }
};

#endif
