#ifndef INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_
#define INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_

namespace Pgn
{
  class PgnMoveTextItem
  {
  public:
    virtual PgnMoveTextItem* Clone() const = 0;
    virtual ~PgnMoveTextItem() {};
  };
}

#endif // INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_
