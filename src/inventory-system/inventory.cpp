#include "inventory.hpp"

// Source: https://stackoverflow.com/questions/61047811/game-inventory-system
// Answered by: Kerek on stackoverflow

// void Inventory::addItem(Item &item)
// {

// }

std::vector<size_t> Inventory::find_indexes_of(const Item& item) const
{
  std::vector<size_t> indexes{};

  for (size_t idx = 0; idx < MAX_INV_SIZE; ++idx) 
  {
    if (inventory_items_[idx].getItemID() == item.getItemID()) 
    {
      indexes.push_back(idx);
    }
  }

  return indexes;
}

size_t Inventory::find_next_empty_slot() const
{
  for (size_t idx = 0; idx < MAX_INV_SIZE; ++idx) 
  {
    if (is_slot_empty(idx)) 
    {
      return idx;
    }
  }
  return MAX_INV_SIZE;
}

bool Inventory::addItemToExistingStack(Item &item)
{
  auto slot_with_same_item = find_indexes_of(item);

  for (auto idx : slot_with_same_item)
  {
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
  size_t next_empty_slot = find_next_empty_slot();

  if (next_empty_slot >= 0) 
  {
    this->inventory_items_[next_empty_slot] = std::move(item);
    return true;
  }

  return false;
}

bool Inventory::addItem(Item &&item)
{
  bool was_possible_to_add_to_existing_stack = addItemToExistingStack(item);

  if (!was_possible_to_add_to_existing_stack)
  {
    return addItemToNewStack(std::move(item));
  }

  return false;
}
