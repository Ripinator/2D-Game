#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "window.hpp"
#include "game.hpp"

int main(int argc, char *args[])
{
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  Window window;
  int w, h;

  SDL_Rect bounds;
  if (SDL_GetDisplayBounds(0, &bounds) == 0)
  {
    w = bounds.w;
    h = bounds.h;
  }

  
  
  if (!window.init("Swordlord", w, h))
  {
    printf("Failed to initialize SDL.\n");
    return 1;
  }

  SDL_SetWindowFullscreen(window.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);

  gameLoop(window);

  window.close();
  SDL_Quit();
  return 0;
}
