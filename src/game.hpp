#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <cstdio> 
#include <string>
#include "window.hpp"

enum class GameState
{
  Menu = 1,
  Play = 2,
  Pause = 3,
  Settings = 4,
  Quit = 5,
  OverlayActive = 6,
  OverlayInactive = 7,
  None = 8
};

enum class OverlayState
{
  Inventory = 0,
  Console = 1,
  QuitConsole = 2,
  None = 3
};

void gameLoop(Window &window); 

#endif
