#include <cstdint>

#include <UnitTest++.h>

#include <Chessboard.hpp>

namespace Pgn
{
  SUITE(ChessBoardTests)
  {
    TEST(DefaultConstructor)
    {
      Chessboard cb;
    }

    TEST(FenConstructor)
    {
      Chessboard cb1("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
      Chessboard cb2("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");
      Chessboard cb3("r3k3/1pp1q3/Q7/2n3pP/4R3/2N5/1PPP4/rB2K2R w Kq - 0 1 ");
    }

    TEST(Pinned)
    {
      Chessboard cb("b3q2k/7q/8/3BRB2/r2RKR2/3BRB2/8/8 w - - 0 1");

      Bitboard expected = bb_positions[27]
                          | bb_positions[35]
                          | bb_positions[36]
                          | bb_positions[37];

      Bitboard pinned = GetPinnedPieces(cb, Color::WHITE);
      CHECK(pinned == expected);

    }

    TEST(MakeMove)
    {
      Chessboard cb("1r2k2r/p1Ppqp2/bn2pn2/3PN1pP/1p2P3/2N2Q1p/PPPBBPP1/R3K2R w KQk g6 0 1");

      Chessboard cb1 = cb;
      cb1.MakeMove(4, 6, PieceType::NONE);
      CHECK(cb1[6] == Piece(PieceType::KING, Color::WHITE));
      CHECK(cb1[5] == Piece(PieceType::ROOK, Color::WHITE));

      cb1 = cb;
      cb1.MakeMove(4, 2, PieceType::NONE);
      CHECK(cb1[2] == Piece(PieceType::KING, Color::WHITE));
      CHECK(cb1[3] == Piece(PieceType::ROOK, Color::WHITE));

      cb1 = cb;
      cb1.MakeMove(14, 23, PieceType::NONE);
      CHECK(cb1[23] == Piece(PieceType::PAWN, Color::WHITE));
      CHECK(cb1[14] == Piece());

      cb1 = cb;
      cb1.MakeMove(12, 19, PieceType::NONE);
      CHECK(cb1[19] == Piece(PieceType::BISHOP, Color::WHITE));
      CHECK(cb1[12] == Piece());

      cb1 = cb;
      cb1.MakeMove(50, 57, PieceType::QUEEN);
      CHECK(cb1[57] == Piece(PieceType::QUEEN, Color::WHITE));
      CHECK(cb1[50] == Piece());

      cb1 = cb;
      cb1.MakeMove(39, 46, PieceType::NONE);
      CHECK(cb1[46] == Piece(PieceType::PAWN, Color::WHITE));
      CHECK(cb1[39] == Piece());
      CHECK(cb1[38] == Piece());
    }
  }
}
