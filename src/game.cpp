#include "game.hpp"
#include "menus/start_menu.hpp" 
#include "game_scene.hpp"
#include "menus/settings_menu.hpp"
#include "menus/console.hpp"
#include "menus/inventory_menu.hpp"
#include <limits.h>
#include <iostream>
#include <memory>

void gameLoop(Window &window)
{
  SDL_Renderer *renderer = window.getRenderer();
  TTF_Font* headerFont = TTF_OpenFont("assets/fonts/MedievalSharp-Regular.ttf", 48);
  TTF_Font* bodyFont = TTF_OpenFont("assets/fonts/CinzelDecorative-Bold.ttf", 24);
  GameState state = GameState::Menu;
  OverlayState overlay_state = OverlayState::None;
  GameState previousState = GameState::None;
  bool console_created = false;

  Scene* currentScene = nullptr;
  Overlay* currentOverlay = nullptr;

  std::unique_ptr<StartMenu> start_menu;
  std::unique_ptr<GameScene> game_scene;
  std::unique_ptr<SettingsMenu> settings_menu;
  std::unique_ptr<InventoryMenu> inventory_menu;
  std::unique_ptr<Console> console_overlay;

  // Initialize start_menu and set currentScene to it
  start_menu = std::make_unique<StartMenu>(window, headerFont, bodyFont, state, overlay_state);
  currentScene = start_menu.get();

  bool running = true;
  SDL_Event event;
  float frameDelay = 1.0f / 250.0f;
  Uint64 last_frame_time = SDL_GetPerformanceCounter();

  while (running)
  {
    Uint64 now = SDL_GetPerformanceCounter();
    const float delta_time = static_cast<float>(now - last_frame_time) / SDL_GetPerformanceFrequency();
    last_frame_time = now;

    while (SDL_PollEvent(&event)) 
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }

      if (currentOverlay && currentScene->OverlayPresent())
      {
        currentOverlay->handleEvent(event);
      }
      else if (currentScene)
      {
        currentScene->handleEvent(event);
      }
    }

    currentScene->update(delta_time);
    if (currentOverlay && currentScene->OverlayPresent())
    {
      currentOverlay->update(delta_time);
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    currentScene->render();

    // std::cout << "OverlayPresent: " << currentScene->OverlayPresent()
    //       << ", overlay_state: " << static_cast<int>(overlay_state)
    //       << ", currentOverlay: " << (currentOverlay ? "yes" : "no") << std::endl;

    if (currentOverlay && currentScene->OverlayPresent())
    {
      currentOverlay->render();
    }
    SDL_RenderPresent(renderer);

    if (state != previousState)
    {
      if (state == GameState::Play)
      {
        if (!game_scene)
        {
          game_scene = std::make_unique<GameScene>(window, state, overlay_state);
        }
        currentScene = game_scene.get();
      }
      else if (state == GameState::Settings)
      {
        if (!settings_menu)
        {
          settings_menu = std::make_unique<SettingsMenu>(window, headerFont, bodyFont, state);
        }
        currentScene = settings_menu.get();
      }
      else if (state == GameState::Quit)
      {
        running = false;
      }
      else if (state == GameState::Menu)
      {
        if (!start_menu)
        {
          start_menu = std::make_unique<StartMenu>(window, headerFont, bodyFont, state, overlay_state);
        }
        currentScene = start_menu.get();
      }
      state = previousState; 
    }


    if (overlay_state != OverlayState::None && currentScene->OverlayPresent())
    {
      if (overlay_state == OverlayState::Inventory)
      {
        if (!inventory_menu) 
        {
          inventory_menu = std::make_unique<InventoryMenu>(window, bodyFont, overlay_state, state);
        }
        currentOverlay = inventory_menu.get();
      }

      if (overlay_state == OverlayState::Console)
      {
        if (!console_overlay)
        {
          console_overlay = std::make_unique<Console>(window, bodyFont, overlay_state ,state);
        }
        currentOverlay = console_overlay.get();
      }
    }
    else
    {
      currentOverlay = nullptr;
    }
    // if (state == GameState::Play)
    //   {
    //     printf("gge");
    //   }

    

    Uint64 frame_end_time = SDL_GetPerformanceCounter();
    float frame_time = static_cast<float>(frame_end_time - now) / SDL_GetPerformanceFrequency();
    if (frame_time < frameDelay)
    {
      Uint64 delay_ms = static_cast<Uint64>((frameDelay - frame_time) * 1000.0f);
      SDL_Delay(delay_ms);
    }
  }
}
