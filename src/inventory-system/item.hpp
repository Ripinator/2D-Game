#ifndef ITEM_HPP
#define ITEM_HPP
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum class ItemType
{
  Weapon = 0,
  Armor = 1,
  Potion = 2,
  Coin = 3
};


class Item
{
  private:
    ItemType type_;
    int ItemID_;
    bool stackable_;
    size_t max_amount_;
    size_t current_amount_;
    //asset from here: https://xflomasterx.itch.io/coins-free
    SDL_Texture *item_icon_texture_;
    SDL_Surface *item_icon_surface_;

  public:
    Item(ItemType type, size_t ItemID, bool stackable, size_t max_amount_) : type_(type), ItemID_(ItemID), stackable_(stackable) {}
    ~Item() = default;

    ItemType getType() const { return type_; }
    void setType(ItemType type) { type_ = type;}
    int getItemID() const { return ItemID_; }
    bool isStackable() { return stackable_; }
    size_t getCurrentAmount() { return current_amount_; }
    size_t getMaxAmount() const { return max_amount_; }
    bool addToStack(size_t amount);
};

#endif
