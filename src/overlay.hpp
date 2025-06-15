#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#include <SDL2/SDL.h>

class Overlay
{
  public:
    virtual ~Overlay() = default;
    virtual void handleEvent(const SDL_Event& event) = 0;
    virtual void update(float delta_time) = 0;
    virtual void render() = 0;
};

#endif