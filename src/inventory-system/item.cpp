#include "item.hpp"

bool Item::addToStack(size_t amount)
{
  if (current_amount_ + amount <= max_amount_)
  {
    current_amount_ += amount;
    return true;
  }
  else
  {
    return false;
  }
}
