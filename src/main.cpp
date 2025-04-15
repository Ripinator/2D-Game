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
  if (!window.init("Swordlord", 1920, 1080))
  {
    printf("Failed to initialize SDL.\n");
    return 1;
  }

  gameLoop(window);


  bool quit = false;
  SDL_Event e;
  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  window.close();
  SDL_Quit();
  return 0;
}
