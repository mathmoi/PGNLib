#ifndef INCLUDE_BITBOARD_HPP_
#define INCLUDE_BITBOARD_HPP_

#include <cstdint>
#include <cstdlib>

#include "BitboardConstants.hpp"

namespace Pgn
{
  typedef size_t Position;
  typedef uint64_t Bitboard;

  const Bitboard Bitboard_MAX = UINT64_MAX;

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

  // Returns the position of the least significant set bit in the bitboard passed in parameters.
  inline unsigned int BitSearch(Bitboard bb);

  // Returns the bitboard passed in parameter with it's LSB bit reset
  // to zero.
  inline Bitboard ResetLSB(Bitboard b);

  // Given two standard square coordinates (0..63) returns the 0x88 
  // differences (0..239).
  inline unsigned int x88diff(int f, int t) { return t - f + (t|7) - (f|7) + 120; };

  inline Bitboard RotateLeft (Bitboard x, int s) { return (x << s) | (x >> (64-s)); };

  inline Bitboard GetObstructed(Position f, Position t) { return RotateLeft(obstructed_by_0x88_diff[x88diff(f, t)], f); };

  // Return direction that link two positions.
  inline Direction GetDirection(Position f, Position t) { return directions_by_0x88_diff[x88diff(f, t)]; };
}

#include "Bitboard-inl.hpp"

#endif // INCLUDE_BITBOARD_HPP_
