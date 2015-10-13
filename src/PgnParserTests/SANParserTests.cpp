#include "../catch/catch.hpp"

#include "../PgnParser/SANParser.hpp"

using namespace m8db;

TEST_CASE("(SANParser")
{
   Chessboard cb("r3k3/1pp1q1P1/Q7/2n3pP/3PR3/2N5/1PP5/rB2K2R w Kq g6 0 1");

   PgnMove m1 = ParseSanMove(cb, "Rxe7+");
   REQUIRE(m1.to() == static_cast<Position>(52)); // e7: 52
   REQUIRE(m1.from() == static_cast<Position>(28)); // e4: 28

   PgnMove m2 = ParseSanMove(cb, "g8=Q");
   REQUIRE(m2.from() == static_cast<Position>(54)); // g7: 54
   REQUIRE(m2.promotion_piece_type() == PieceType::QUEEN);

   PgnMove m3 = ParseSanMove(cb, "b3");
   REQUIRE(m3.from() == static_cast<Position>(9)); // b2: 9

   PgnMove m4 = ParseSanMove(cb, "b4");
   REQUIRE(m4.from() == static_cast<Position>(9)); // b2: 9

   PgnMove m5 = ParseSanMove(cb, "dxc5");
   REQUIRE(m5.from() == static_cast<Position>(27)); // d4: 27

   PgnMove m6 = ParseSanMove(cb, "hxg6");
   REQUIRE(m6.from() == static_cast<Position>(39)); // h5: 39
}

TEST_CASE("(SANParserAmbiguousMoves")
{
   Chessboard cb("1k6/4q1q1/PP6/KP2q1P1/PP3B2/2P5/2q5/6q1 b - - 0 1");

   PgnMove m = ParseSanMove(cb, "Q1xg5");
   REQUIRE(m.from() == static_cast<Position>(6)); // g1: 6

   m = ParseSanMove(cb, "Qg7xg5");
   REQUIRE(m.from() == static_cast<Position>(54)); // g7: 54

   m = ParseSanMove(cb, "Qexg5");
   REQUIRE(m.from() == static_cast<Position>(52)); // e7: 52

   m = ParseSanMove(cb, "Qcxc3");
   REQUIRE(m.from() == static_cast<Position>(10)); // c2: 10

   m = ParseSanMove(cb, "Q5c7");
   REQUIRE(m.from() == static_cast<Position>(36)); // e5: 36

   m = ParseSanMove(cb, "Q7c7");
   REQUIRE(m.from() == static_cast<Position>(52)); // e7: 36
}