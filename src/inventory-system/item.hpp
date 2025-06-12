#ifndef ITEM_HPP
#define ITEM_HPP

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
    const int ItemID_;
    bool stackable_;
    int max_amount_;
    int current_amount_;

  public:
    Item(ItemType type, int ItemID, bool stackable) : type_(type), ItemID_(ItemID), stackable_(stackable) {}
    ~Item() = default;

    ItemType getType() { return type_; }
    void setType(ItemType type) { type_ = type;}
    int getItemID() { return ItemID_; }
    bool getStackable() { return stackable_; }
};

#endif