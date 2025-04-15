#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <cstdio> 

class MainMenu
{
  private:
    SDL_Renderer *renderer_;
    SDL_Rect menu_rect_;
  
  public:
    MainMenu(SDL_Renderer *renderer, const SDL_Rect &menu_rect) 
    : renderer_{renderer}, menu_rect_{menu_rect} {}

    MainMenu(const MainMenu&) = delete;
    MainMenu& operator=(const MainMenu&) = delete;
    ~MainMenu() = default;

  void drawMainMenu();

};

#endif
