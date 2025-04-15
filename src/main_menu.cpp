#include "main_menu.hpp"
#include "window.hpp"

void MainMenu::drawMainMenu()
{
  Window window;
  SDL_Window *game_window = window.getWindow();

  SDL_Renderer* renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf("Creating the renderer failed! ERROR:%s\n", SDL_GetError());
    return;
  }

  SDL_Rect menuRect = {0, 0, 0, 0};

  return;
}