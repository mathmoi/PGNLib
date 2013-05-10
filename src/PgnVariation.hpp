#ifndef INCLUDE_PGN_VARIATION_HPP_
#define INCLUDE_PGN_VARIATION_HPP_

#include <memory>
#include <vector>
#include <stdexcept>

#include "PgnMoveTextItem.hpp"

namespace PgnParser
{
  class InvalidItemException : public std::runtime_error
  {
  public:
    InvalidItemException()
      : std::runtime_error("An invalid items was added to a PgnVariation.") {};
  };


  class PgnVariation : public PgnMoveTextItem
  {
  public:
    typedef std::shared_ptr<PgnMoveTextItem> ItemPointer;
    typedef std::shared_ptr<const PgnMoveTextItem> ConstItemPointer;
    typedef std::vector<ItemPointer> ItemsVector;

    typedef ItemsVector::iterator iterator;
    typedef ItemsVector::const_iterator const_iterator;

  private:
    unsigned int first_move_number_;
    ItemsVector items_;

  public:
    inline PgnMoveTextItemType get_type() const { return ITEM_VARIATION; };

    inline void set_first_move_number(unsigned int first_move_number) { first_move_number_ = first_move_number; };
    inline unsigned int get_first_move_number() const { return first_move_number_; };

    inline ItemPointer operator[](unsigned int n) { return items_[n]; };
    inline ConstItemPointer operator[](unsigned int n) const { return std::const_pointer_cast<const PgnMoveTextItem>(items_[n]); };

    inline iterator begin() { return items_.begin(); };
    inline const_iterator begin() const { return items_.begin(); };
    inline iterator end() { return items_.end(); };
    inline const_iterator end() const { return items_.end(); };

    inline void push_back(const ItemPointer& item);

    // This function insert a new element, val, just before the position 
    // pointer by the iterator, it.
    inline void insert(iterator it, const ItemPointer& val) { items_.insert(it, val); };

    // Erase the element pointed by the iterator, it.
    inline void erase(iterator it) { items_.erase(it); };
  };
}

#include "PgnVariation-inl.hpp"

#endif // INCLUDE_PGN_VARIATION_HPP_
