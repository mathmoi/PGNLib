#include <fstream>

#include <UnitTest++.h>
#include <Piece.hpp>

namespace PgnLib
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

