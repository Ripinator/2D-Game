#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "window.hpp"
#include "game.hpp"

// int createMainMenu(SDL_Window *window)
// {
//   SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//   if (renderer == NULL)
//   {
//     printf("Creating the renderer failed! ERROR:%s\n", SDL_GetError());
//     return -1;
//   }

//   SDL_Rect menuRect = {0, 0, 0, 0};
//   MainMenu mainMenu(renderer, menuRect);

//   mainMenu.drawMenu();

//   return 0;
// }

int main(int argc, char *args[])
{
  SDL_Init(SDL_INIT_VIDEO);

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
