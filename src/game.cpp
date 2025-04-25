
#include "game.hpp"
#include "start_menu.hpp" 
#include "game_scene.hpp"
#include "settings_menu.hpp"
#include <limits.h>
#include <iostream>
#include <memory>

void gameLoop(Window &window)
{
  SDL_Renderer *renderer = window.getRenderer();
  TTF_Font* headerFont = TTF_OpenFont("assets/fonts/MedievalSharp-Regular.ttf", 48);
  TTF_Font* bodyFont = TTF_OpenFont("assets/fonts/CinzelDecorative-Bold.ttf", 24);
  GameState state = GameState::Menu;
  GameState previousState = GameState::None;

  std::unique_ptr<Scene> currentScene = std::make_unique<StartMenu>(window, headerFont, bodyFont, state);

  bool running = true;
  SDL_Event event;
  const float frameDelay = 1.0f / 250.0f;
  Uint64 last_frame_time = SDL_GetPerformanceCounter();
  
  while (running)
  {
    
    Uint64 now = SDL_GetPerformanceCounter();
    float delta_time = static_cast<float>(now - last_frame_time) / SDL_GetPerformanceFrequency();
    last_frame_time = now;
    
    while (SDL_PollEvent(&event)) 
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
      currentScene->handleEvent(event);
    }

    currentScene->update(delta_time);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    currentScene->render();
    SDL_RenderPresent(renderer);

    if (state != previousState)
    {
      // i only switch into the play state if the state is play and iam currently in the startmenu
      if (state == GameState::Play)
      {
        currentScene = std::make_unique<GameScene>(window, state);
      }
      else if (state == GameState::Settings)
      {
        currentScene = std::make_unique<SettingsMenu>(window, headerFont, bodyFont, state);
      }
      else if (state == GameState::Quit)
      {
        running = false;
      }
      else if (state == GameState::Menu)
      {
        currentScene = std::make_unique<StartMenu>(window, headerFont, bodyFont, state);
      }
      previousState = state;
    }
    
    Uint64 frame_end_time = SDL_GetPerformanceCounter();
    float frame_time = static_cast<float>(frame_end_time - now) / SDL_GetPerformanceFrequency();
    if (frame_time < frameDelay)
    {
      Uint64 delay_ms = static_cast<Uint64>((frameDelay - frame_time) * 1000.0f);
      SDL_Delay(delay_ms);
    }
  }
}
