#include "../include/PgnVariation.hpp"
#include "../include/PgnGame.hpp"
#include "../include/PgnMove.hpp"

#include <iostream>

namespace Pgn
{
  PgnVariation::PgnVariation(const PgnVariation& other)
    : first_move_number_(other.first_move_number_),
      first_move_white_(other.first_move_white_)
  {
    for (auto item : other.items_)
    {
      items_.push_back(item->Clone());
    }
  }

  PgnVariation::PgnVariation(PgnVariation&& other) noexcept
  {
    Swap(other);
  }

  PgnVariation& PgnVariation::operator=(PgnVariation other)
  {
    Swap(other);
    return *this;
  }

  PgnVariation& PgnVariation::operator=(PgnVariation&& other)
  {
    Swap(other);
    return *this;
  }

  PgnVariation::~PgnVariation() noexcept
  {
    for(auto& item : items_)
    {
      delete item;
    }
  }

  void PgnVariation::Swap(PgnVariation& other)
  {
    std::swap(first_move_number_, other.first_move_number_);
    std::swap(first_move_white_, other.first_move_white_);
    items_.swap(other.items_);   
  }

  void PgnVariation::push_back(const ItemPointer& item)
  {
    if (!item
        || dynamic_cast<const PgnGame*>(item))
    {
      throw InvalidItemException();
    }

    items_.push_back(item);
  }
}

