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
    }
  }
}
