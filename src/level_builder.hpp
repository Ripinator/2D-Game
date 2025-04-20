#ifndef LEVEL_BUILDER_HPP
#define LEVEL_BUILDER_HPP

#include "window.hpp"
#include "enemies.hpp"
#include "utils/utils.hpp"
#include <memory>
#include <SDL2/SDL_ttf.h>
#include <vector>

class LevelBuilder
{
  private:
    Window& window_;
    SDL_Renderer *renderer_;
    int screen_width_;
    int screen_height_;

    SDL_Rect floor_rect_;
    SDL_Point player_spawn_;
    std::vector<std::unique_ptr<Enemy>> enemies_;
    std::vector<SDL_Texture*> background_layers_;
    std::vector<SDL_Rect> platforms_;

  public:
    LevelBuilder(Window &window, int screen_width, int screen_height, SDL_Rect floor_rect);
    void loadLevel(int levelId);
    SDL_Point &getPlayerSpawn() const;
    std::vector<std::unique_ptr<Enemy>> &getEnemies() const;
    std::vector<SDL_Texture*> &getBackgroundLayers() const;
};

#endif