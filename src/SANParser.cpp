#include "SANParser.hpp"

#include <iostream>

namespace Pgn
{
  Position GetOrigineMove(const Chessboard& board, Piece p, Position to, bool is_capture, Bitboard from)
  {
    // First we get a bitboard of the candidates origins. The way to get it 
    // depends on the piece type.
    Bitboard candidates;
    switch (p.type())
    {
    case PieceType::ROOK:
      candidates = RookAttacks(board.occupancy(), to) & board.bb_piece(p);
      break;

    case PieceType::BISHOP:
      candidates = BishopAttacks(board.occupancy(), to) & board.bb_piece(p);
      break;

    case PieceType::QUEEN:
      candidates = (RookAttacks(board.occupancy(), to) | BishopAttacks(board.occupancy(), to)) & board.bb_piece(p);
      break;

    case PieceType::KNIGHT:
      candidates = bb_knight_attacks[to] & board.bb_piece(p);
      break;

    case PieceType::KING:
      candidates = bb_king_attacks[to] & board.bb_piece(p);
      break;

    case PieceType::PAWN:
      if (is_capture)
      {
        // If the pawn move is a capture it's origin candidates will be on the 
        // left and right columns, one row behind the to square. The direction 
        // of the move depends on the color of the pawn.
        Bitboard b = bb_positions[to];
        b &= ~bb_files[0]; // We remove the position if it's in the a file.
        candidates = (p.color() == Color::BLACK ? b << 7 : b >> 9);  // Get the left candidate.

        b = bb_positions[to];
        b &= ~bb_files[7]; // We remove the position if in the h file
        candidates |= (p.color() == Color::BLACK ? b << 9 : b >> 7);  // Get the left candidate.

        candidates &= board.bb_piece(p);
      }
      else
      {
        // The pawn move is not a capture. We need to get candidates for the normal moves and 
        // the two square initials moves.
        Bitboard b = bb_positions[to];
        b = (p.color() == Color::BLACK ? b << 8 : b >> 8);
        candidates = b & board.bb_piece(p);

        b &= ~board.occupancy();
        b = (p.color() == Color::BLACK ? b << 8 : b >> 8);
        candidates |= b & board.bb_piece(p);
      }
      break;

    case PieceType::NONE:
      break;
    }

    // We only keep candidates that overlaps with the from bitboard;
    candidates &= from;

    // If candidates are pinned we keep them only if the ray defined by the 
    // piece and the destination is the same as the ray defined by the piece 
    // and it's king. This way the piece still "protect" the king.
    Bitboard pinned = GetPinnedPieces(board, p.color());
    pinned &= candidates;
    if (pinned)
    {
      Position king_position = BitSearch(board.bb_piece(Piece(PieceType::KING, p.color())));

      do
      {
        Position from = BitSearch(pinned);
        pinned = ResetLSB(pinned);
        if (GetDirection(from, to) != GetDirection(from, king_position))
        {
          candidates ^= bb_positions[from];
        }
      } while (pinned);
    }

    // If there is not candidate or if there is more than one we throw 
    // an exceptions
    if (candidates == 0
        || (candidates & (candidates - 1)) != 0)
    {
      throw InvalidMoveException();
    }

    Position origin = BitSearch(candidates);
    return origin;
  }

  PgnMove ParseSanMove(const Chessboard& board, const std::string& san)
  {
    /*if (san == "dxc1=Q")
    {
      std::cout <<"Hello" <<std::endl;
    }*/


    Position from;
    Position to;
    Piece piece;
    Piece captured_piece;
    PieceType promotion_piece_type = PieceType::NONE;
    Bitboard bb_from_candidates = Bitboard_MAX;
    bool is_capture = false;

    if (san.substr(0, 5) == "O-O-O")
    {
      from = board.next_to_move() == Color::WHITE ? 4 : 60;
      to = board.next_to_move() == Color::WHITE ? 2 : 58;
      piece = Piece(PieceType::KING, board.next_to_move());
    }
    else if (san.substr(0, 3) == "O-O")
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
          promotion_piece_type = CHAR_TO_PIECE_TYPE_MAP.at(*end);
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

      // If the first character is a piece it's moved piece, otherwise the moved piece 
      // is a pawn.
      if (begin <= end && *begin >= 'A' && *begin <= 'Z')
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

      // If there is a 'x' character at the end it means the move is a capture
      if (begin <= end && *end == 'x')
      {
        // If this is a prise en passant
        if (piece.type() == PieceType::PAWN
            && file_index == board.en_passant_column()
            && rank_index == 5 - static_cast<size_t>(board.next_to_move()) * 3)
        {
          captured_piece = Piece(PieceType::PAWN, GetOtherSide(board.next_to_move()));
        }
        else
        {
          captured_piece = board[to];
        }
        is_capture = true;
        --end;

        // if the captured piece is NONE or of the side to move next we throw 
        // an exception
        if (captured_piece.type() == PieceType::NONE
            || captured_piece.color() == board.next_to_move())
        {
          throw InvalidMoveException();
        }
      }

      // if the first character is a file, it's the origin file. In that 
      // case we must restrict bb_from_candidates to that file.
      if (begin <= end && *begin >= 'a' && *begin <= 'h')
      {
        uint_fast8_t file_index = *begin - 'a';
        bb_from_candidates = bb_files[file_index];
        ++begin;
      }

      // If the first character rank, it's the origin rank, In that cast we 
      // must restrict bb_from_candidates to that rank.
      if (begin <= end && *begin >= '1' && *begin <= '8')
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
      from = GetOrigineMove(board, piece, to, is_capture, bb_from_candidates);
    }

    return PgnMove(from, to, promotion_piece_type);
  }
}
