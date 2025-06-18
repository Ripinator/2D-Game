#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#include <SDL2/SDL.h>
#include "colors.hpp"

class Overlay
{
  public:
    virtual ~Overlay() = default;
    virtual void handleEvent(const SDL_Event& event) = 0;
    virtual void update(float delta_time) = 0;
    virtual void render() = 0;
    const int BASE_WIDTH = 1920;
    const int BASE_HEIGHT = 1080;
};

#endif