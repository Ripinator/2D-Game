#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#define MAX_PLAYER_ATTACKS 100
#include "scene.hpp"
#include "game.hpp"
#include "window.hpp"
#include "tile.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <vector>
#include <array>

class Player;

class Enemy
{
  protected:
    SDL_Renderer *renderer_;
    SDL_Texture *sprite_;
    SDL_Surface *sprite_surface_;
    SDL_FRect enemy_rect_;
    SDL_Rect floor_rect_;
    SDL_FRect health_bar_;
    SDL_FRect health_bar_border_;
    int health_;
    int damage_;
    int speed_;
    bool attack_done_;
    bool is_dead_and_gone_;

  public:
    Enemy(Window &window, const SDL_Rect &floor_rect)
    : renderer_(window.getRenderer()), floor_rect_(floor_rect) {}
    virtual void update(Player &player, const SDL_FRect& player_box, const std::array<SDL_FRect, 100> &player_attacks_hitboxes, float delta_time) = 0;
    virtual void render() = 0;
    virtual SDL_FRect getCollisionBox() = 0;
    virtual void setTiles(std::vector<Tile> *tiles) = 0;
    virtual void setEnemyPosition(int x, int y) = 0;
    virtual void setCameraOffset(int x, int y) = 0;
    virtual void takeDamage(int amount)
    {
      health_ -= amount;
    }
    SDL_FRect getRect() const { return enemy_rect_; }
    bool isAlive() const { return health_ > 0; }
    bool isDeadAndGone() { return is_dead_and_gone_; }
};

#endif