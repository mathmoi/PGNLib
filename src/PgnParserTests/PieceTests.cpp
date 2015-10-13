#include "../catch/catch.hpp"

#include "../PgnParser/Piece.hpp"

TEST_CASE("PieceTests")
{
   m8db::Piece p(m8db::PieceType::KING, m8db::Color::WHITE);
   REQUIRE(m8db::PieceType::KING == p.type());
   REQUIRE(m8db::Color::WHITE == p.color());
}