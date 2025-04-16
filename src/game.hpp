#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <cstdio> 
#include <string>
#include "window.hpp"

enum class gameState
{
  Menu = 1,
  Play = 2,
  Pause = 3
};

void gameLoop(Window &window);

#endif
