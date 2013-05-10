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

    inline const std::string& move() const { return move_; };
    inline void set_move(std::string move) { move_ = move; };
  };
}

#endif // INCLUDE_PGN_MOVE_HPP_
