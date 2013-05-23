#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/Bitboard.hpp"
#include "../src/BitboardConstants.hpp"

namespace Pgn
{
  SUITE(BitboardTests)
  {
    TEST(RookAttacksEmptyBoard)
    {
      Bitboard occ = 0;
      Position rook_position = 27; // d4
      Bitboard expected_attacks = bb_positions[24]
                                  | bb_positions[24]
                                  | bb_positions[25]
                                  | bb_positions[26]
                                  | bb_positions[28]
                                  | bb_positions[29]
                                  | bb_positions[30]
                                  | bb_positions[31]
                                  | bb_positions[3]
                                  | bb_positions[11]
                                  | bb_positions[19]
                                  | bb_positions[35]
                                  | bb_positions[43]
                                  | bb_positions[51]
                                  | bb_positions[59];

      Bitboard attacks = RookAttacks(occ, rook_position);
      CHECK_EQUAL(expected_attacks, attacks);
    }

    TEST(RookAttacksSommeOccupiedSquares)
    {
      Position rook_position = 27; // d4

      Bitboard occ = bb_positions[24]
                     | bb_positions[51]
                     | bb_positions[29]
                     | bb_positions[19]
                     | bb_positions[36];

      Bitboard expected_attacks = bb_positions[24]
                                  | bb_positions[24]
                                  | bb_positions[25]
                                  | bb_positions[26]
                                  | bb_positions[28]
                                  | bb_positions[29]
                                  | bb_positions[19]
                                  | bb_positions[35]
                                  | bb_positions[43]
                                  | bb_positions[51];

      Bitboard attacks = RookAttacks(occ, rook_position);
      CHECK_EQUAL(expected_attacks, attacks);
    }

    TEST(BishopAttacksEmptyBoard)
    {
      Bitboard occ = 0;
      Position bishop_position = 27; // d4
      Bitboard expected_attacks = bb_positions[0]
                                  | bb_positions[9]
                                  | bb_positions[18]
                                  | bb_positions[36]
                                  | bb_positions[45]
                                  | bb_positions[54]
                                  | bb_positions[63]
                                  | bb_positions[48]
                                  | bb_positions[41]
                                  | bb_positions[34]
                                  | bb_positions[20]
                                  | bb_positions[13]
                                  | bb_positions[6];

      Bitboard attacks = BishopAttacks(occ, bishop_position);
      CHECK_EQUAL(expected_attacks, attacks);
    }

    TEST(BishopAttacksSommeOccupiedSquares)
    {
      Position bishop_position = 27; // d4

      Bitboard occ = bb_positions[48]
                     | bb_positions[63]
                     | bb_positions[54]
                     | bb_positions[20]
                     | bb_positions[28]
                     | bb_positions[26];

      Bitboard expected_attacks = bb_positions[0]
                                  | bb_positions[9]
                                  | bb_positions[18]
                                  | bb_positions[36]
                                  | bb_positions[45]
                                  | bb_positions[54]
                                  | bb_positions[48]
                                  | bb_positions[41]
                                  | bb_positions[34]
                                  | bb_positions[20];

      Bitboard attacks = BishopAttacks(occ, bishop_position);
      CHECK_EQUAL(expected_attacks, attacks);
    }
  }
}
