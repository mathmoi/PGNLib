#ifndef INGLUDE_PGN_VARIATION_INL_HPP_
#define INGLUDE_PGN_VARIATION_INL_HPP_

namespace PgnParser
{
  // Foward declaration of PgnGame to prevent having to include the file here.
  class PgnGame;

  inline void PgnVariation::push_back(const ItemPointer& item)
  {
    if (!item
        || std::dynamic_pointer_cast<PgnGame>(item))
    {
      throw InvalidItemException();
    }

    items_.push_back(item);
  }
}

#endif // INGLUDE_PGN_VARIATION_INL_HPP_
