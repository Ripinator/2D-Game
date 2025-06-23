#include "inventory.hpp"
#include <cassert>

// Source: https://stackoverflow.com/questions/61047811/game-inventory-system
// Answered by: Kerek on stackoverflow
Inventory::Inventory(OccupantType type, size_t inventory_size, std::vector<Item> items)
  : type_(type), inventory_slots_(inventory_size)
{
  if (items.empty()) 
  {
    inventory_items_ = std::vector<Item>(inventory_slots_, Item());
  } 
  else 
  {
    inventory_items_ = std::move(items);
  }

  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_");
}

std::vector<size_t> Inventory::find_indexes_of(const Item& item) const
{
  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_");
  std::vector<size_t> indexes{};

  for (size_t idx = 0; idx < inventory_slots_; idx++) 
  {
    assert(idx < inventory_items_.size());
    if (inventory_items_[idx].getItemID() == item.getItemID()) 
    {
      indexes.push_back(idx);
    }
  }

  return indexes;
}

size_t Inventory::find_next_empty_slot() const
{
  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_");
  for (size_t idx = 0; idx < inventory_slots_; ++idx) 
  {
    assert(idx < inventory_items_.size());
    if (is_slot_empty(idx)) 
    {
      return idx;
    }
  }
  return inventory_slots_;
}

bool Inventory::addItemToExistingStack(Item &item)
{
  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_");
  auto slot_with_same_item = find_indexes_of(item);

  for (auto idx : slot_with_same_item)
  {
    assert(idx < inventory_items_.size());
    if (item.getItemID() == inventory_items_[idx].getItemID())
    {
      if (inventory_items_[idx].addToStack(item.getCurrentAmount()))
      {
        return true;
      }
    }
  }

  return false;
}

bool Inventory::addItemToNewStack(Item &&item)
{
  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_");
  size_t next_empty_slot = find_next_empty_slot();

  if (next_empty_slot < inventory_items_.size()) 
  {
    this->inventory_items_[next_empty_slot] = std::move(item);
    return true;
  }

  return false;
}

bool Inventory::addItem(Item &&item)
{
  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_");
  bool was_possible_to_add_to_existing_stack = addItemToExistingStack(item);

  if (!was_possible_to_add_to_existing_stack)
  {
    return addItemToNewStack(std::move(item));
  }

  return true;
}

void Inventory::initializeItems(size_t inventory_size)
{
  inventory_items_ = std::vector<Item>(inventory_size, Item());
  inventory_slots_ = inventory_size;
  assert(inventory_items_.size() == inventory_slots_ && "inventory_items_ size must match inventory_slots_ after initialization");
}
