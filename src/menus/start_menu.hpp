#ifndef START_MENU_HPP
#define START_MENU_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class StartMenu : public Scene 
{
  private:
    SDL_Renderer *renderer_;
    SDL_Rect menu_rect_;
    SDL_Rect settings_menu_rect_;
    SDL_Rect quit_rect_;
    SDL_Rect start_rect_;
    SDL_Rect border_rect_;
    SDL_Rect text_header_rect_;
    SDL_Rect text_quit_rect_;
    SDL_Rect text_start_rect_;
    SDL_Rect text_settings_rect_;
    TTF_Font *header_font_;
    TTF_Font *font_;
    GameState &game_state_;
    OverlayState &overlay_state_;
    SDL_Event event_;
    SDL_Texture *text_texture_header_;
    SDL_Texture *text_texture_start_;
    SDL_Texture *text_texture_quit_;
    SDL_Texture *text_texture_settings_;
    SDL_Texture *blue_background_texture_;
    SDL_Texture *white_clouds_texture_;
    SDL_Texture *blue_clouds_texture_;
    SDL_Texture *water_texture_;
    SDL_Texture *grass_1_texture_;
    SDL_Texture *grass_2_texture_;
    SDL_Texture *grass_3_texture_;
    static Mix_Music *main_theme_music_;
    int screen_width_;
    int screen_height_;
    bool overlay_active_;

  public:
    StartMenu(Window &window, TTF_Font *header_font, TTF_Font *font, GameState &game_state, OverlayState &overlay_state);
    ~StartMenu();
    void handleEvent(const SDL_Event &event) override;
    void update(float delta_time) override;
    void drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &text_rect, bool hovered, SDL_Event &event);
    SDL_Texture *createText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Rect& outRect);
    void render() override;
    void setType(GameState game_state);
    bool OverlayPresent() override { return overlay_active_; }
};

#endif
