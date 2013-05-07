#ifndef INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_
#define INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_

namespace PgnParser
{
  enum PgnMoveTextItemType
  {
    ITEM_MOVE,
    ITEM_NAG,
    ITEM_VARIATION,
    ITEM_COMMENT
  };

  class PgnMoveTextItem
  {
  public:
    virtual PgnMoveTextItemType get_type() const = 0;
  };
}

#endif // INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_
