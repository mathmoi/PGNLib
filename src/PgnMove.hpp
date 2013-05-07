#ifndef INCLUDE_PGN_MOVE_HPP_
#define INCLUDE_PGN_MOVE_HPP_

namespace PgnParser
{
  class PgnMove : public PgnMoveTextItem
  {
  private:
    std::string move_;

  public:
    PgnMove(std::string move)
      : move_(move)
    {};

    inline const std::string& get_move() const { return move_; };
    inline void set_move(std::string move) { move_ = move; };

    inline PgnMoveTextItemType get_type() const { return ITEM_MOVE; };
  };
}

#endif // INCLUDE_PGN_MOVE_HPP_
