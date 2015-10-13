#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cctype>

#include "Chessboard.hpp"
#include "Utils.hpp"
#include "Bitboard.hpp"

namespace m8db
{
  std::unordered_map<char, Piece> CreateCharPieceMap()
  {
    std::unordered_map<char, Piece> map;
    map['R'] = Piece(PieceType::ROOK, Color::WHITE);
    map['r'] = Piece(PieceType::ROOK, Color::BLACK);
    map['N'] = Piece(PieceType::KNIGHT, Color::WHITE); 
    map['n'] = Piece(PieceType::KNIGHT, Color::BLACK);
    map['B'] = Piece(PieceType::BISHOP, Color::WHITE); 
    map['b'] = Piece(PieceType::BISHOP, Color::BLACK);
    map['Q'] = Piece(PieceType::QUEEN, Color::WHITE); 
    map['q'] = Piece(PieceType::QUEEN, Color::BLACK);
    map['K'] = Piece(PieceType::KING, Color::WHITE); 
    map['k'] = Piece(PieceType::KING, Color::BLACK);
    map['P'] = Piece(PieceType::PAWN, Color::WHITE); 
    map['p'] = Piece(PieceType::PAWN, Color::BLACK);
    return map;
  }

  const std::unordered_map<char, Piece> CHAR_PIECE_MAP = CreateCharPieceMap();
  
  // Map characters to castling flags
  std::unordered_map<char, uint_fast8_t> CreateCharCastlingFlagsMap()
  {
    std::unordered_map<char, uint_fast8_t> map;
    map['K'] = static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::WHITE);
    map['Q'] = static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::WHITE);
    map['k'] = static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(Color::BLACK);
    map['q'] = static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(Color::BLACK);
    return map;
  }

  const std::unordered_map<char, uint_fast8_t> CHAR_CASTLING_FLAGS_MAP = CreateCharCastlingFlagsMap();
          
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

    for (std::uint8_t i = 0; i < 8; ++i)
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
      else if (std::isdigit(static_cast<unsigned char>(c)))
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

  Bitboard GetPinnedPieces(const Chessboard& board, Color color)
  {
    Position king_position = BitSearch(board.bb_piece(Piece(PieceType::KING, color)));
    Color opposite_color = GetOtherSide(color);
    Bitboard op_rook_queen = board.bb_piece(Piece(PieceType::ROOK, opposite_color)) | board.bb_piece(Piece(PieceType::QUEEN, opposite_color));
    Bitboard op_bishop_queen = board.bb_piece(Piece(PieceType::BISHOP, opposite_color)) | board.bb_piece(Piece(PieceType::QUEEN, opposite_color));

    Bitboard pinned = 0;
    Bitboard pinner = XRayRookAttacks(board.occupancy(), board.bb_colors(color), king_position) & op_rook_queen;
    while (pinner)
    {
      Position sq = BitSearch(pinner);
      pinned |= GetObstructed(sq, king_position) & board.bb_colors(color);
      pinner = ResetLSB(pinner);
    }

    pinner = XRayBishopAttacks(board.occupancy(), board.bb_colors(color), king_position) & op_bishop_queen;
    while (pinner)
    {
      Position sq = BitSearch(pinner);
      pinned |= GetObstructed(sq, king_position) & board.bb_colors(color);
      pinner = ResetLSB(pinner);
    }

    return pinned;
  }

  void Chessboard::MakeMove(Position from, Position to, PieceType promotion_piece_type)
  {
    Piece piece = board_[from];

    uint_fast8_t first_rank = static_cast<uint_fast8_t>(piece.color()) * 7;

	  uint_fast8_t rank_from = static_cast<uint_fast8_t>(from / 8);
  	uint_fast8_t file_from = static_cast<uint_fast8_t>(from % 8);
    uint_fast8_t rank_to = static_cast<uint_fast8_t>(to / 8);
    uint_fast8_t file_to = static_cast<uint_fast8_t>(to % 8);

    // If there is no piece on the from square we throw an exception
    if (piece.type() == PieceType::NONE)
    {
      throw InvalidMakeMoveException("No piece on the from square");
    }

    // If the moved piece is not from the color on move we throw an exception.
    if (next_to_move_ != piece.color())
    {
      throw InvalidMakeMoveException("Piece from the wrong side");
    }

    // If it's a prise en passant. We detect the prise en passant by the 
    // fact that 1) the move is diagonal, 2) There is no piece on the target 
    // square and 3) the target square is on the en_passant_column.
    if (piece.type() == PieceType::PAWN
        && abs(static_cast<int>(from % 8) - static_cast<int>(to % 8)) == 1
        && board_[to].type() == PieceType::NONE
        && to % 8 == en_passant_column_)
    {
      Position pos_piece_taken = to - 8 + 16 * static_cast<std::uint_fast8_t>(piece.color());
      RemovePiece(pos_piece_taken);
    }

    // If it's a capture we remove the captured piece.
    if (board_[to].type() != PieceType::NONE)
    {
      RemovePiece(to);
    }

    // If it's a two square king move we must move the rook accordingly to 
    // castle rules.
    if (piece.type() == PieceType::KING
        && abs(static_cast<int>(from) - static_cast<int>(to)) == 2)
    {
      // If it's a queen side castle
      if (file_to == 2)
      {
        AddPiece(rank_to * 8 + 3, board_[rank_to * 8]);
        RemovePiece(rank_to * 8);
      }
      else if (file_to == 6)
      {
        AddPiece(rank_to * 8 + 5, board_[rank_to * 8 + 7]);
        RemovePiece(rank_to * 8 + 7);
      }
      else
      {
        throw InvalidMakeMoveException("Invalid king (castle?) move");
      }
    }

    // We move the piece
    RemovePiece(from);
    AddPiece(to, piece);

    // If it's a promotion we need to change the pawn into the promoted piece.
    if (promotion_piece_type != PieceType::NONE)
    {
      RemovePiece(to);
      AddPiece(to, Piece(promotion_piece_type, piece.color()));
    }

    // If it's a two square pawn move we must set the en_passant_column_.
    if (piece.type() == PieceType::PAWN
        && abs(static_cast<int>(from) - static_cast<int>(to)) == 16)
    {
      en_passant_column_ = file_from;
    }
    else
    {
      en_passant_column_ = NO_EN_PASSANT;
    }

    // If it's a move on the first rank we need to further check if it affects 
    // castling rights.
    if (rank_from == first_rank)
    {
      if (file_from == 0 || file_from == 4)
      {
        castling_flags_ &= ~(static_cast<uint_fast8_t>(Castle::QUEEN_SIDE) << static_cast<uint_fast8_t>(piece.color()));
      }

      if (file_from == 7 || file_from == 4)
      {
        castling_flags_ &= ~(static_cast<uint_fast8_t>(Castle::KING_SIDE) << static_cast<uint_fast8_t>(piece.color()));
      }
    }
    
    next_to_move_ = GetOtherSide(next_to_move_);
  }
}
