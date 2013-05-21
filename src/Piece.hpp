#ifndef INCLUDE_PIECE_HPP_
#define INCLUDE_PIECE_HPP_

namespace Pgn
{
  enum class Color : size_t
  {
    WHITE = 0,
    BLACK = 1
  };

  enum class PieceType : size_t
  {
    NONE = 0,
    PAWN = 2,
    KNIGHT = 4,
    BISHOP = 10,
    ROOK = 12,
    QUEEN = 14,
    KING = 6
  };

  class Piece
  {
  private:
    size_t piece_;

  public:
    inline Piece()
      : piece_(static_cast<size_t>(PieceType::NONE))
     {};

    inline Piece(PieceType t, Color c)
      : piece_(static_cast<size_t>(t) + static_cast<size_t>(c))
     {};

     inline PieceType type() const { return static_cast<PieceType>(piece_ & ~1); };
     inline Color color() const { return static_cast<Color>(piece_ & 1); };

     inline bool slide() const { return piece_ & 8; };
     inline bool slide_like_rook() const { return (piece_ & 6) == 6; }

     inline operator size_t() const { return piece_; };
  };
}

#endif // INCLUDE_PIECE_HPP_
