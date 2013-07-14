#include <cassert>

namespace Pgn
{
  void Chessboard::AddPiece(Position pos, Piece piece)
  {
    Bitboard bb_position = static_cast<Bitboard>(1) << pos;

    // A: The position is currently empty
    assert((occupancy_ & bb_position) == 0);

    board_[pos] = piece; 
    bb_pieces_[piece] |= bb_position;
    bb_colors_[static_cast<size_t>(piece.color())] |= bb_position;
    occupancy_ |= bb_position;
  }

  void Chessboard::RemovePiece(Position pos)
  {
    Bitboard bb_position = static_cast<Bitboard>(1) << pos;

    // A: There is a piece at the position
    assert((occupancy_ & bb_position) != 0);

    bb_pieces_[board_[pos]] ^= bb_position;
    bb_colors_[static_cast<size_t>(board_[pos].color())] ^= bb_position;
    board_[pos] = Piece(PieceType::NONE, Color::WHITE);
    occupancy_ ^= bb_position;
  }
}
