#ifndef INCLUDE_PGN_VARIATION_HPP_
#define INCLUDE_PGN_VARIATION_HPP_

#include <memory>
#include <vector>

#include "PgnMoveTextItem.hpp"

namespace PgnParser
{
  class PgnVariation : public PgnMoveTextItem
  {
  public:
    typedef std::vector<std::shared_ptr<PgnMoveTextItem>> ItemsVector;
  private:
    unsigned int first_move_number_;
    ItemsVector items_;

  public:
    inline PgnMoveTextItemType get_type() const { return ITEM_VARIATION; };
    inline void set_first_move_number(unsigned int first_move_number) { first_move_number_ = first_move_number; };
    inline unsigned int get_first_move_number() const { return first_move_number_; };

    /*
     * This function returns a reference to the iternal array containing the 
     * items. Doing this does not enforce the encapsulation, but it does
     * simplify the interfaces.
     */
    inline ItemsVector& get_items() { return items_; }
  };
}

#endif // INCLUDE_PGN_VARIATION_HPP_
