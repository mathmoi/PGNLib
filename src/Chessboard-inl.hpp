#include <cassert>

namespace Pgn
{
  Chessboard::Chessboard()
  {
    next_to_move_ = Color::WHITE;

    for (size_t i = 16; i <= 47; ++i)
    {
      board_[i] = Piece();
    }

    occupancy_ = 0;

    bb_pieces_[Piece(PieceType::PAWN, Color::WHITE)] = 0;
    bb_pieces_[Piece(PieceType::ROOK, Color::WHITE)] = 0;
    bb_pieces_[Piece(PieceType::KNIGHT, Color::WHITE)] = 0;
    bb_pieces_[Piece(PieceType::BISHOP, Color::WHITE)] = 0;
    bb_pieces_[Piece(PieceType::KING, Color::WHITE)] = 0;
    bb_pieces_[Piece(PieceType::QUEEN, Color::WHITE)] = 0;

    bb_pieces_[Piece(PieceType::PAWN, Color::BLACK)] = 0;
    bb_pieces_[Piece(PieceType::ROOK, Color::BLACK)] = 0;
    bb_pieces_[Piece(PieceType::KNIGHT, Color::BLACK)] = 0;
    bb_pieces_[Piece(PieceType::BISHOP, Color::BLACK)] = 0;
    bb_pieces_[Piece(PieceType::KING, Color::BLACK)] = 0;
    bb_pieces_[Piece(PieceType::QUEEN, Color::BLACK)] = 0;

    bb_colors_[static_cast<size_t>(Color::WHITE)] = 0;
    bb_colors_[static_cast<size_t>(Color::BLACK)] = 0;
    
    castling_flags_ = static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::WHITE)
                      & static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::WHITE)
                      & static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::BLACK)
                      & static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::BLACK);

    en_passant_column_ = NO_EN_PASSANT;

    static const std::array<PieceType, 8> pieces_to_add = 
        {{PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN,
          PieceType::KING, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK}};

    for (size_t i = 0; i < 8; ++i)
    {
      AddPiece(i, Piece(pieces_to_add[i], Color::WHITE));
      AddPiece(56 + i, Piece(pieces_to_add[i], Color::BLACK));
      AddPiece(8 + i, Piece(PieceType::PAWN, Color::WHITE));
      AddPiece(48 + i, Piece(PieceType::PAWN, Color::BLACK));
    }

  }

  void Chessboard::AddPiece(Position pos, Piece piece)
  {
    Bitboard bb_position = static_cast<Bitboard>(1) << pos;

    // A: The position is currently empty
    assert((occupancy_ & bb_position) == 0);

    board_[pos] = piece; 
    bb_pieces_[piece] |= bb_position;
    bb_colors_[static_cast<size_t>(piece.color())] |= bb_position;
  }

  void Chessboard::RemovePiece(Position pos)
  {
    Bitboard bb_position = static_cast<Bitboard>(1) << pos;

    // A: There is a piece at the position
    assert((occupancy_ & bb_position) != 0);

    bb_pieces_[board_[pos]] ^= bb_position;
    bb_colors_[static_cast<size_t>(board_[pos].color())] ^= bb_position;
    board_[pos] = Piece(PieceType::NONE, Color::WHITE);
  }
}
