#ifndef INCLUDE_PGN_MOVE_HPP_
#define INCLUDE_PGN_MOVE_HPP_

#include "Piece.hpp"
#include "PgnMoveTextItem.hpp"

namespace Pgn
{
  typedef size_t Position;

  class PgnMove : public PgnMoveTextItem
  {
  private:
    std::string move_;

    Position from_;
    Position to_;
    Piece piece_;
    Piece captured_piece_;
    Piece promotion_piece_;
  public:
    // TODO : REMOVE THIS CONSTRUCTOR
    PgnMove(std::string move)
      : move_(move),
        from_(0),
        to_(0)
    {};

    PgnMove(Position from, Position to, Piece piece, Piece captured_piece, Piece promotion_piece)
      : from_(from),
        to_(to),
        piece_(piece),
        captured_piece_(captured_piece),
        promotion_piece_(promotion_piece)
    {};
    
    inline const std::string& move() const { return move_; };
    inline void set_move(std::string move) { move_ = move; };

    inline Position from() const { return from_; };
    inline void set_from(Position from) { from_ = from; };

    inline Position to() const { return to_; };
    inline void set_to(Position to) { to_ = to; };

    inline Piece piece() const { return piece_; };
    inline void set_piece(Piece piece) { piece_ = piece; };

    inline Piece captured_piece() const { return captured_piece_; };
    inline void set_captured_piece(Piece captured_piece) { captured_piece_ = captured_piece; };

    inline Piece promotion_piece() const { return promotion_piece_; };
    inline void set_promotion_piece(Piece promotion_piece) { promotion_piece_ = promotion_piece; };
  };
}

#endif // INCLUDE_PGN_MOVE_HPP_
