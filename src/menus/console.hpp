#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "SDL2/SDL_ttf.h"
#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include <iostream>
#include <vector>

class Console
{
  private:
    SDL_Renderer *renderer_;
    Window &window_;
    SDL_Event event_;
    SDL_Rect console_rect_;
    // The console top bar is the grey bar which says console
    SDL_Rect console_top_bar_rect_;
    SDL_Rect console_top_bar_text_rect_;
    SDL_Rect command_line_rect_;
    SDL_Rect command_line_text_rect_;
    SDL_Rect command_line_border_rect_;
    // The cursor that shows you where you are in a text editor(here the commandline)
    SDL_Rect block_cursor_;
    SDL_Rect input_text_rect_;
    SDL_Texture *texture_console_top_bar_text_;
    SDL_Texture *text_texture_command_line_;
    SDL_Texture *input_text_texture_;
    TTF_Font *font_;
    GameState &game_state_;
    int width_;
    int height_;
    std::string input_text_;

  public:
    Console(Window &window, TTF_Font *font, GameState &game_state);
    ~Console();
    SDL_Texture *createText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Rect &outRect);
    void handleEvent(const SDL_Event &event);
    void update(float delta_time);
    void render();
};

#endif