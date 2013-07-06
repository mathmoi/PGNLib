#ifndef INCLUDE_CHESS_BOARD_HPP_
#define INCLUDE_CHESS_BOARD_HPP_

#include <array>
#include <string>
#include <stdexcept>

#include "Piece.hpp"
#include "BitboardConstants.hpp"

namespace Pgn
{
  typedef size_t Position;

  const size_t MAX_INDEX_PIECE = 15;
  const uint_fast8_t NO_EN_PASSANT = 8;

  enum class Castle
  {
    KING_SIDE = 0,
    QUEEN_SIDE = 1
  };

  class BadFenException : public std::runtime_error
  {
  public:
    BadFenException()
      : std::runtime_error("Could not parse the FEN string.") {};
  };

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
    Chessboard();

    // Initialize the chessboard with a fen encoded position
    Chessboard(const std::string& fen);

    inline Bitboard occupancy() const { return occupancy_; };
    inline Bitboard bb_piece(Piece p) const { return bb_pieces_[p]; };
    inline Bitboard bb_colors(Color c) const { return bb_colors_[static_cast<size_t>(c)]; };
    inline Color next_to_move() const { return next_to_move_; };
    inline Piece operator[] (Position p) const { return board_[p]; };
    inline size_t en_passant_column () const { return en_passant_column_; };
    inline bool castling_flag(Color color, Castle castle) const { return castling_flags_ & (static_cast<uint_fast8_t>(castle) << static_cast<uint_fast8_t>(color)); };  

    void MakeMove(Position from, Position to, Piece promotion_piece);

  private:   
    inline void AddPiece(Position pos, Piece piece);
    inline void RemovePiece(Position pos);

    // This function emptys the Chessboard, initializing all members. It is 
    // used by constructors.
    void Empty();
  };

  // This function returns a bitboard of the pieces of a particular color that 
  // are pinned to their king.
  Bitboard GetPinnedPieces(const Chessboard& board, Color color);
}

#include "Chessboard-inl.hpp"

#endif // INCLUDE_CHESS_BOARD_HPP_
