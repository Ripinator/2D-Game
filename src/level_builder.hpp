#ifndef LEVEL_BUILDER_HPP
#define LEVEL_BUILDER_HPP

#include "window.hpp"
#include "enemies.hpp"
#include "utils/utils.hpp"
#include <memory>
#include <SDL2/SDL_ttf.h>
#include <vector>

struct Tile
{
  SDL_Texture *texture;
  SDL_Rect destRect;
  bool solid;
};

struct LevelData {
  SDL_Point playerSpawn;
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<Tile> tiles;
  std::vector<SDL_Texture*> backgrounds;
};

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
    std::vector<Tile> tiles_;

  public:
    LevelBuilder(Window &window, int screen_width, int screen_height, SDL_Rect floor_rect);
    LevelData loadLevel(int levelId);
};

#endif