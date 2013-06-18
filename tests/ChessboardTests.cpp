#include <cstdint>
#include <iostream>

#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/Chessboard.hpp"

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
  }
}
