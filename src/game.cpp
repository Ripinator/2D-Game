
#include "game.hpp"
#include "start_menu.hpp" 
#include "game_scene.hpp"
#include "settings_menu.hpp"
#include <limits.h>
#include <iostream>

void gameLoop(Window &window)
{
  SDL_Renderer *renderer = window.getRenderer();
  TTF_Font* headerFont = TTF_OpenFont("assets/fonts/MedievalSharp-Regular.ttf", 48);
  TTF_Font* bodyFont = TTF_OpenFont("assets/fonts/CinzelDecorative-Bold.ttf", 24);
  GameState state = GameState::Menu;

  Scene* currentScene = new StartMenu(window, headerFont, bodyFont, state);

  bool running = true;
  SDL_Event event;
  const int frameDelay = 1000 / 60;

  while (running)
  {
    Uint32 frameStart = SDL_GetTicks();
    
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

    // i only switch into the play state if the state is play and iam currently in the startmenu
    if (state == GameState::Play && dynamic_cast<StartMenu*>(currentScene))
    {
      delete currentScene;
      currentScene = new GameScene(window, state);
    }
    else if (state == GameState::Settings)
    {
      delete currentScene;
      currentScene = new SettingsMenu(window, headerFont, state);
    }
    else if (state == GameState::Quit)
    {
      delete currentScene;
      currentScene = nullptr;
      running = false;
      break;
    }

    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < frameDelay)
    {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  delete currentScene;
}
