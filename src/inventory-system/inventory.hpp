#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include <inventory-system/item.hpp>
#include <vector>
#include <cassert>

enum class OccupantType
{
  Player = 0,
  Enemy = 1,
  Boss = 2,
  Chest = 3
};


class Inventory
{
  private:
    OccupantType type_;
    size_t inventory_slots_;
    std::vector<Item> inventory_items_;
    bool is_full_;
    static constexpr size_t MAX_INV_SIZE = 40;
    static constexpr int INVENTORY_EMPTY_SLOT_ID = -1;
    std::vector<size_t> find_indexes_of(const Item &item) const;
    bool is_slot_empty(size_t idx) const { return inventory_items_[idx].getItemID() == INVENTORY_EMPTY_SLOT_ID; }
    size_t find_next_empty_slot() const;
    bool addItemToExistingStack(Item &item_to_add);
    bool addItemToNewStack(Item &&item_to_add);

  public:
    Inventory(OccupantType type, int inventory_slots, std::vector<Item> inventory_items);
    ~Inventory() = default;

    bool addItem(Item &&item_to_add);
    void removeItem(Item &item_to_delete);
    bool getFull() { return is_full_; }
    size_t getInventorySize() { return inventory_slots_; }
    void setInventorySize(size_t inventory_size) { inventory_slots_ = inventory_size; }
    void initializeItems(size_t inventory_size);
    ItemType getItemTypeOfSlot(int vector_idx) 
    {
      assert(vector_idx >= 0 && static_cast<size_t>(vector_idx) < inventory_items_.size());
      return inventory_items_[vector_idx].getType(); 
    }
};

#endif
