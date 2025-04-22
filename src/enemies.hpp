#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include "tile.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <vector>

class Enemy
{
  protected:
    SDL_Renderer *renderer_;
    SDL_Texture *sprite_;
    SDL_Surface *sprite_surface_;
    SDL_Rect enemy_rect_;
    SDL_Rect floor_rect_;
    int health_;
    int damage_;
    int speed_;

  public:
    Enemy(Window &window, const SDL_Rect &floor_rect)
    : renderer_(window.getRenderer()), floor_rect_(floor_rect) {}
    virtual void update() = 0;
    virtual void render() = 0;
    virtual SDL_Rect getCollisionBox() = 0;
    virtual void setTiles(std::vector<Tile> *tiles) = 0;
    virtual void setEnemyPosition(int x, int y) = 0;
    virtual void setCameraOffset(int x, int y) = 0;
    virtual void takeDamage(int amount)
    {
      health_ -= amount;
    }
    SDL_Rect getRect() const {return enemy_rect_;}
    bool isAlive() const {return health_ > 0;}
};

#endif