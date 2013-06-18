#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/SANParser.hpp"
#include "../src/Chessboard.hpp"

namespace Pgn
{
  SUITE(SANParserTests)
  {
    TEST(SANParser)
    {
      Chessboard cb("r3k3/1pp1q1P1/Q7/2n3pP/3PR3/2N5/1PP5/rB2K2R w Kq g6 0 1");

      PgnMove m1 = ParseSanMove(cb, "Rxe7+");
      CHECK(m1.piece() == Piece(PieceType::ROOK, Color::WHITE));
      CHECK_EQUAL(m1.to(), static_cast<Position>(52)); // e7: 52
      CHECK_EQUAL(m1.from(), static_cast<Position>(28)); // e4: 28
      CHECK(m1.captured_piece() == Piece(PieceType::QUEEN, Color::BLACK));

      PgnMove m2 = ParseSanMove(cb, "g8=Q");
      CHECK_EQUAL(m2.from(), static_cast<Position>(54)); // g7: 54
      CHECK(m2.piece() == Piece(PieceType::PAWN, Color::WHITE));
      CHECK(m2.promotion_piece() == Piece(PieceType::QUEEN, Color::WHITE));

      PgnMove m3 = ParseSanMove(cb, "b3");
      CHECK_EQUAL(m3.from(), static_cast<Position>(9)); // b2: 9
      CHECK(m3.piece() == Piece(PieceType::PAWN, Color::WHITE));

      PgnMove m4 = ParseSanMove(cb, "b4");
      CHECK_EQUAL(m4.from(), static_cast<Position>(9)); // b2: 9

      PgnMove m5 = ParseSanMove(cb, "dxc5");
      CHECK_EQUAL(m5.from(), static_cast<Position>(27)); // d4: 27

      PgnMove m6 = ParseSanMove(cb, "hxg6");
      CHECK_EQUAL(m6.from(), static_cast<Position>(39)); // h5: 39
    }
  }
}
