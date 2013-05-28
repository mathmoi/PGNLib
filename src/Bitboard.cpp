#include "Bitboard.hpp"
#include "BitboardConstants.hpp"

namespace Pgn
{
  // returns the column index of the position p.
  size_t File(Position p)
  {
    return p & 0x7;
  }

  size_t Rank(Position p)
  {
    return p >> 3;
  }

  Bitboard RookAttacks(Bitboard occupancy, Position rook_position)
  {
    // We extract the line occupancy (row_occ).
    //    rook_position & 0x38 : Get the index of the square at the begining of
    //                           the line of rook_position.
    //    
    //    + 1 : We then add 1 to this value because we don't need the first 
    //          column in the row occupancy (we only need the 6 inner squares.
    //
    //    >> : We shift the occupancy by ((rook_position & 0x38) + 1) to get 
    //         the row occupancy in the least significants bits.
    //
    //    & 0x3f : We keep only the six least significants bits.
    size_t row_occ = static_cast<size_t>((occupancy >> ((rook_position & 0x38) + 1)) & 0x3F);

    // We get the lines attacks.
    Bitboard attacks = bb_rank_attacks[File(rook_position)][row_occ] & bb_ranks[rook_position];

    // Similarly we get the column occupancy and the columns attacks
    size_t col_occ = static_cast<size_t>((((occupancy & bb_files[rook_position]) >> (File(rook_position))) * (UINTMAX_C(0x0102040810204080) * 2)) >> (64 - 6));
    attacks |= (bb_file_attacks[Rank(rook_position)][col_occ] & bb_files[rook_position]);

    return attacks;
  }

  Bitboard BishopAttacks(Bitboard occupancy, Position bishop_position)
  {
    // We use an algorithm similar to RookAttacks, see it's comments.
    // The algorithm used to calculate the diagonals occupancy is described 
    // here : http://chessprogramming.wikispaces.com/Kindergarten+Bitboards

    size_t diag_occ = static_cast<size_t>(((occupancy & bb_diagonals[bishop_position]) * UINTMAX_C(0x0202020202020202)) >> (64 - 6));
    Bitboard attacks = bb_rank_attacks[File(bishop_position)][diag_occ] & bb_diagonals[bishop_position];

    size_t anti_diag_occ = static_cast<size_t>(((occupancy & bb_reverse_diagonals[bishop_position]) * UINTMAX_C(0x0202020202020202)) >> (64 - 6));
    attacks |= (bb_rank_attacks[File(bishop_position)][anti_diag_occ] & bb_reverse_diagonals[bishop_position]);

    return attacks;
  }

  Bitboard XRayRookAttacks(Bitboard occupancy, Bitboard blockers, Position rook_position)
  {
    Bitboard attacks = RookAttacks(occupancy, rook_position);
    blockers &= attacks;
    return attacks ^ RookAttacks(occupancy ^ blockers, rook_position);
  }

  Bitboard XRayBishopAttacks(Bitboard occupancy, Bitboard blockers, Position bishop_position)
  {
    Bitboard attacks = BishopAttacks(occupancy, bishop_position);
    blockers &= attacks;
    return attacks ^ BishopAttacks(occupancy ^ blockers, bishop_position);
  }
}
