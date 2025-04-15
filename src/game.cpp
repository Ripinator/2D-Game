#include "game.hpp"
#include "main_menu.hpp" 

void gameLoop(Window &window)
{
  SDL_Renderer *renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    SDL_Log("Renderer creation failed: %s", SDL_GetError());
  }

  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event)) 
    {
      if (event.type == SDL_QUIT) 
      {
        running = false;
      }
    }
  }
}
