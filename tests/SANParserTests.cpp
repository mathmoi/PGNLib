#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/SANParser.hpp"
#include "../src/Chessboard.hpp"

namespace Pgn
{
  SUITE(SANParserTests)
  {
    TEST(SANParser)
    {
      Chessboard cb("r3k3/1pp1q3/Q7/2n3pP/4R3/2N5/1PPP4/rB2K2R w Kq - 0 1");

      PgnMove m1 = ParseSanMove(cb, "Rxe7+");
      CHECK(m1.piece() == Piece(PieceType::ROOK, Color::WHITE));
      CHECK_EQUAL(m1.to(), static_cast<Position>(52)); // e7: 52
      CHECK(m1.captured_piece() == Piece(PieceType::QUEEN, Color::BLACK));

      PgnMove m2 = ParseSanMove(cb, "g8=Q");
      CHECK(m2.piece() == Piece(PieceType::PAWN, Color::WHITE));
      CHECK(m2.promotion_piece() == Piece(PieceType::QUEEN, Color::WHITE));


    }
  }
}
