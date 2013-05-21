#ifndef INCLUDE_CHESS_BOARD_HPP_
#define INCLUDE_CHESS_BOARD_HPP_

#include <array>

#include "Piece.hpp"

namespace Pgn
{
  typedef uint64_t Bitboard;
  typedef size_t Position;

  const size_t MAX_INDEX_PIECE = 15;
  const uint_fast8_t NO_EN_PASSANT = 8;

  enum class Castle
  {
    KING_SIDE = 0,
    QUEEN_SIDE = 1
  };

  /*inline Piece PieceType(size_t index)
  {
    return static_cast<Piece>(index & ~1);
  }

  inline Color PieceColor(size_t index)
  {
    return static_cast<Color>(index & 1);
  }*/

  class Chessboard
  {
  private:
    // Which color is next to move?
    Color next_to_move_;

    // Array containing the piece on each square.
    std::array<Piece, 64> board_;

    // Bitboard with a bit set for each square with a piece on it.
    Bitboard occupancy_;

    // Bitboard for each pieces. Note that some positions in the array are not 
    // used because there is more pieces index than there is piece. This allow 
    // an optimisation elsewhere.
    std::array<Bitboard, MAX_INDEX_PIECE + 1> bb_pieces_;

    // Bitboard for each colors.
    std::array<Bitboard, 2> bb_colors_;

    // Castling flags. Indicate if each type of castling is still allowed.
    uint_fast8_t castling_flags_;

    // index of the column of the pawn that can be taken en passant. If no 
    // pawn can be taken en passant the value should be NO_EN_PASSANT.
    uint_fast8_t en_passant_column_;
       
  public:

    // Initialize the chessboard with the standard starting position
    inline Chessboard();

  private:
    inline void AddPiece(Position pos, Piece piece);
    inline void RemovePiece(Position pos);
  };
}

#include "Chessboard-inl.hpp"

#endif // INCLUDE_CHESS_BOARD_HPP_
