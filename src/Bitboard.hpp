#ifndef INCLUDE_BITBOARD_HPP_
#define INCLUDE_BITBOARD_HPP_

#include <cstdint>
#include <cstdlib>

namespace Pgn
{
  typedef size_t Position;
  typedef uint64_t Bitboard;

  // returns the column index of the position p.
  size_t File(Position p);

  // return the row index of the position p.
  size_t Rank(Position p);

  // Returns a bitboard with bits set for each positions attacked by a rook
  // given the board occupancy and rook position passed in parameters.
  Bitboard RookAttacks(Bitboard occupancy, Position rook_position);

  // Returns a bitboard with bits set for each positions attacked by a bishop
  // given the board occupancy and bishop position passed in parameters.
  Bitboard BishopAttacks(Bitboard occupancy, Position bishop_position);

  // Returns a bitboard with bits set for each positions attacked by a rook on
  // rook_position through blockers on the squares identified by the
  // blockers Bitboard.
  Bitboard XRayRookAttacks(Bitboard occupancy, Bitboard blockers, Position rook_position);

  // Returns a bitboard with bits set for each positions attacked by a bishop 
  // on rook_position through blockers on the squares identified by the
  // blockers Bitboard.
  Bitboard XRayBishopAttacks(Bitboard occupancy, Bitboard blockers, Position bishop_position);
}

#endif // INCLUDE_BITBOARD_HPP_
