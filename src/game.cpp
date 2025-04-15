
#include "game.hpp"
#include "start_menu.hpp" 
#include <unistd.h>
#include <limits.h>
#include <iostream>

void gameLoop(Window &window)
{
  SDL_Renderer *renderer = window.getRenderer();
  TTF_Font* headerFont = TTF_OpenFont("assets/fonts/MedievalSharp-Regular.ttf", 48);
  TTF_Font* bodyFont = TTF_OpenFont("assets/fonts/CinzelDecorative-Bold.ttf", 24);

  Scene* currentScene = new StartMenu(window, headerFont, bodyFont);

  bool running = true;
  SDL_Event event;

  while (running)
  {

    // input handling
    while (SDL_PollEvent(&event)) 
    {
      if (event.type == SDL_QUIT) 
      {
        running = false;
      }
      currentScene->handleEvent(event);
    }

    currentScene->update();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    currentScene->render();

    SDL_RenderPresent(renderer);
  }

  delete currentScene;
}
