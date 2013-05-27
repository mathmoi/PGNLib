#include <string>
#include <vector>
#include <unordered_map>

#include "Chessboard.hpp"
#include "Utils.hpp"

namespace Pgn
{
  void Chessboard::Empty()
  {
    next_to_move_ = Color::WHITE;

    for (size_t i = 0; i < 64; ++i)
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
    
    castling_flags_ = 0;

    en_passant_column_ = NO_EN_PASSANT;
  }

  Chessboard::Chessboard()
  {
    Empty();

    castling_flags_ = static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::WHITE)
                      | static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::WHITE)
                      | static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::BLACK)
                      | static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::BLACK);

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

  Chessboard::Chessboard(const std::string& fen)
  {
    Empty();

    std::vector<std::string> fen_tokens = split(fen, ' ');

    // If we don't have at least the first 3 parts of the fen string we throw 
    // a BadFenException.
    if (fen_tokens.size() < 3)
    {
      throw BadFenException();
    }

    // We parse the first part of the fen string describing the positions 
    // of pieces.
    uint_fast8_t pos = 0;
    for (char c : fen_tokens[0])
    {
      if (c == '/')
      {
        // We ignore the '/' character
      }
      else if (std::isdigit(c))
      {
        // If the character is a digit we increment the position counter and 
        // we check it does not get greater than 64. If it is we throw 
        // an exception.
        pos += c - '0';
        if (pos > 64)
        {
          throw BadFenException();
        }
      }
      else
      {
        // If the execution gets here, the character must represent a piece.
        // If it does not we have an invalid fen string. We also need to check
        // that 'pos' is not passed the board size.
        if (pos > 63)
        {
          throw BadFenException();
        }

        // This map is used to convert from char to Piece types.
        static const std::unordered_map<char, Piece> CHAR_PIECE_MAP =
          {
            {'R', Piece(PieceType::ROOK, Color::WHITE)}, {'r', Piece(PieceType::ROOK, Color::BLACK)},
            {'N', Piece(PieceType::KNIGHT, Color::WHITE)}, {'n', Piece(PieceType::KNIGHT, Color::BLACK)},
            {'B', Piece(PieceType::BISHOP, Color::WHITE)}, {'b', Piece(PieceType::BISHOP, Color::BLACK)},
            {'Q', Piece(PieceType::QUEEN, Color::WHITE)}, {'q', Piece(PieceType::QUEEN, Color::BLACK)},
            {'K', Piece(PieceType::KING, Color::WHITE)}, {'k', Piece(PieceType::KING, Color::BLACK)},
            {'P', Piece(PieceType::PAWN, Color::WHITE)}, {'p', Piece(PieceType::PAWN, Color::BLACK)}
          };

        try
        {
          Piece piece = CHAR_PIECE_MAP.at(c);
          Position internal_pos = 56 - (pos/8) * 8 + (pos % 8); // Translate from FEN position to internal position.
          AddPiece(internal_pos, piece);
          ++pos;
        }
        catch (std::out_of_range)
        {
          throw BadFenException();
        }
      }
    }

    // TODO : Check we have one and only one king on each side.

    // We parse the second part of the fen string that indicate which side is 
    // to move next.
    if (fen_tokens[1] == "w")
    {
      next_to_move_ = Color::WHITE;
    }
    else if (fen_tokens[1] == "b")
    {
      next_to_move_ = Color::BLACK;
    }
    else
    {
      throw BadFenException();
    }

    // We parse the third part of the fen string which contains the castling 
    // rights for the position. If the string is just "-" it means there is
    // no castling right and we have nothing to do.
    if (fen_tokens[2] != "-")
    {
      // Map characters to castling flags
      static const std::unordered_map<char, uint_fast8_t> CHAR_CASTLING_FLAGS_MAP = 
        {
          {'K', static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::WHITE)},
          {'Q', static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::WHITE)},
          {'k', static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::BLACK)},
          {'q', static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::BLACK)}
        };

      for (char c : fen_tokens[2])
      {
        try
        {
          castling_flags_ |= CHAR_CASTLING_FLAGS_MAP.at(c);
        }
        catch (std::out_of_range)
        {
          throw BadFenException();
        }
      }
    }

    // If there is a fourth part and it's not "-" it must be the prise en passant square.
    if (fen_tokens.size() >= 4
        && fen_tokens[3] != "-")
    {
      if (fen_tokens[3].size() == 2
          && fen_tokens[3][0] >= 'a' && fen_tokens[3][0] <= 'h'
          && fen_tokens[3][1] >= '0' && fen_tokens[3][1] <= '8')
      {
        en_passant_column_ = fen_tokens[3][0] - 'a';
      }
      else
      {
        throw BadFenException();
      }
    }
  }
}
