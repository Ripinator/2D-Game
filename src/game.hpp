#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <cstdio> 
#include <string>
#include "window.hpp"

typedef enum gameState_
{
  GameMode_Menu = 1,
  GameMode_Game = 2,
  GameMode_Pause = 3
};

void gameLoop(Window &window);

#endif