#include "SANParser.hpp"

namespace Pgn
{
  Position GetOrigineMove(const Chessboard& board, Piece p, Position to, Bitboard from)
  {
    return 0;
  }

  PgnMove ParseSanMove(const Chessboard& board, const std::string& san)
  {
    Position from;
    Position to;
    Piece piece;
    Piece captured_piece;
    Piece promotion_piece;
    Bitboard bb_from_candidates = Bitboard_MAX;

    if (san == "O-O-O")
    {
      from = board.next_to_move() == Color::WHITE ? 4 : 60;
      to = board.next_to_move() == Color::WHITE ? 2 : 58;
      piece = Piece(PieceType::KING, board.next_to_move());
    }
    else if (san == "O-O")
    {
      from = board.next_to_move() == Color::WHITE ? 4 : 60;
      to = board.next_to_move() == Color::WHITE ? 6 : 62;
      piece = Piece(PieceType::KING, board.next_to_move());
    }
    else
    {
      auto begin = san.begin();
      auto end = san.end() - 1;

      // If the last charater is a check or mat indicator we ignore it.
      if (*end == '#' || *end == '+')
      {
        --end;
      }

      // If the last character is a piece it's a promotion piece
      if (*end >= 'A' && *end <= 'Z')
      {
        try
        {
          promotion_piece = Piece(CHAR_TO_PIECE_TYPE_MAP.at(*end), board.next_to_move());
          end -= 2;
        }
        catch (std::out_of_range)
        {
          throw InvalidMoveException();
        }
      }

      // The two last characters are the line and column of the destination
      uint_fast8_t rank_index = *end - '1';
      --end;
      uint_fast8_t file_index = *end - 'a';
      --end;
      to = rank_index * 8 + file_index;

      // If the target square is invalid we throw an exception
      if (to < 0 || to >= 64)
      {
        throw InvalidMoveException();
      }

      // If there is a 'x' character at the end it means the move is a capture
      if (*end == 'x')
      {
        captured_piece = board[to];
        --end;

        // if the captured piece is NONE or of the side to move next we throw 
        // an exception
        if (captured_piece.type() == PieceType::NONE
            || captured_piece.color() == board.next_to_move())
        {
          throw InvalidMoveException();
        }
      }

      // If the first character is a piece it's moved piece, otherwise the moved piece 
      // is a pawn.
      if (*begin >= 'A' && *begin <= 'Z')
      {
        try
        {
          piece = Piece(CHAR_TO_PIECE_TYPE_MAP.at(*begin), board.next_to_move());
        }
        catch (std::out_of_range)
        {
          throw InvalidMoveException();
        }
        ++begin;
      }
      else
      {
        piece = Piece(PieceType::PAWN, board.next_to_move());
      }

      // if the first character is a file, it's the origin file. In that 
      // case we must restrict bb_from_candidates to that file.
      if (*begin >= 'a' && *begin <= 'h')
      {
        uint_fast8_t file_index = *begin - 'a';
        bb_from_candidates = bb_files[file_index];
        ++begin;
      }

      // If the first character rank, it's the origin rank, In that cast we 
      // must restrict bb_from_candidates to that rank.
      if (*begin >= '1' && *begin <= '8')
      {
        uint_fast8_t rank_index = *begin - '1';
        bb_from_candidates &= bb_ranks[rank_index * 8];
        ++begin;
      }

      // If we still have characters to parse we throw an exception
      if (begin <= end)
      {
        throw InvalidMoveException();
      }

      // We now get the origin
      from = GetOrigineMove(board, piece, to, bb_from_candidates);
    }

    return PgnMove(from, to, piece, captured_piece, promotion_piece);
  }
}
