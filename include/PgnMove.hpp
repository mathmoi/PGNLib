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
    Position from_;
    Position to_;
    PieceType promotion_piece_type_;
  public:
    PgnMove(Position from, Position to, PieceType promotion_piece_type)
      : from_(from),
        to_(to),
        promotion_piece_type_(promotion_piece_type)
    {};

    inline PgnMoveTextItem* Clone() const { return new PgnMove(from_, to_, promotion_piece_type_); };
    
    inline Position from() const { return from_; };
    inline void set_from(Position from) { from_ = from; };

    inline Position to() const { return to_; };
    inline void set_to(Position to) { to_ = to; };

    inline PieceType promotion_piece_type() const { return promotion_piece_type_; };
    inline void set_promotion_piece_type(PieceType promotion_piece_type) { promotion_piece_type_ = promotion_piece_type; };
  };
}

#endif // INCLUDE_PGN_MOVE_HPP_
