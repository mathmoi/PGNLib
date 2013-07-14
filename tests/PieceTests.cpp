#include <fstream>

#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../include/Piece.hpp"

namespace Pgn
{
  SUITE(PieceTests)
  {
    TEST(Piece)
    {
      Piece p(PieceType::KING, Color::WHITE);
      CHECK(PieceType::KING == p.type());
      CHECK(Color::WHITE == p.color());
    }
  }
}

