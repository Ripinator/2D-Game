#include "inventory.hpp"

// Source: https://stackoverflow.com/questions/61047811/game-inventory-system
// Answered by: Kerek on stackoverflow

void Inventory::addItem(Item &item)
{

}

std::vector<size_t> Inventory::find_indexes_of(const Item& item) const
{
  std::vector<size_t> indexes{};

  for (size_t idx = 0; idx < MAX_INV_SIZE; ++idx) 
  {
    if (items[idx].id == item.id) 
    {
      indexes.push_back(idx);
    }
  }

  return indexes;
}

void Inventory::addItemToExistingStack(Item &item)
{
  auto slot_with_same_item = find_indexes_of(item);

  for (auto idx : slot_with_same_item)
  {
    if (item.getItemID() == )
  }
}