#ifndef INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_
#define INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_

namespace PgnLib
{
  /**
   * Represent an item in the movetext section of a PGN game.
   *
   * This is an abstract class. The move text items can be one of the 
   * following:
   *  * A move
   *  * A comment
   *  * A variation
   *  * A Numerical Annotation Glyph
   *
   * To determine the type of a PgnMoveTextItem you need to use the `typeid`
   * operator or try to cast it with `dynamic_cast<...>(item)`.
   *
   * Example:
   * @code
   * PgnMoveTextItem* item = ...
   * if (typeid(*item) == typeid(PgnMove))
   * {
   *   // item points to a PgnMove
   * }
   * @endcode
   *
   * or
   *
   * @code
   * PgnMoveTextItem* item = ...
   * PgnMove* move = dynamic_cast<PgnMove*>(item);
   * if (move)
   * {
   *  // item is a move.
   * }
   * @endcode
   */
  class PgnMoveTextItem
  {
  public:
    /**
     * Creates a copy of the PgnMoveTextItem.
     *
     * This function create a dynamically allocated copy of the item. The code
     * which calls the function must assume ownership of the allocated memory 
     * and is responsible for releasing it eventually.
     *
     * @return a pointer to a dynamically allocated copy of the object.
     */
    virtual PgnMoveTextItem* Clone() const = 0;

    /**
     * Destructor
     */
    virtual ~PgnMoveTextItem() {};
  };
}

#endif // INCLUDE_PGN_MOVE_TEXT_ITEM_HPP_
