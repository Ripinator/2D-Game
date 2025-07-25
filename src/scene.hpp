#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL2/SDL.h>

class Scene 
{
  private:
    bool overlay_active_;

  public:
    virtual ~Scene() = default;
    virtual void handleEvent(const SDL_Event& event) = 0;
    virtual void update(float delta_time) = 0;
    virtual void render() = 0;
    virtual bool OverlayPresent() = 0;
};

#endif
