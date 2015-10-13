/**
* @file Bitboard-inl.hpp
*
* Contains the Bitboard class definitions.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/

#include <intrin.h>
#pragma intrinsic(_BitScanForward64)

namespace m8db
{
  inline unsigned int BitSearch(Bitboard bb)
  {
#if defined(__GNUC__) && defined(__LP64__)
    asm ("bsfq %0, %0" : "=r" (bb) : "0" (bb));
    return static_cast<unsigned int>(bb);

#elif defined(_MSC_VER) && defined(_WIN64)
    unsigned long index = -1;
    _BitScanForward64(&index, bb);
    return index;

#else
	  const int index64[64] = {
		  0,  1, 48,  2, 57, 49, 28,  3,
		  61, 58, 50, 42, 38, 29, 17,  4,
		  62, 55, 59, 36, 53, 51, 43, 22,
		  45, 39, 33, 30, 24, 18, 12,  5,
		  63, 47, 56, 27, 60, 41, 37, 16,
		  54, 35, 52, 21, 44, 32, 23, 11,
		  46, 26, 40, 15, 34, 20, 31, 10,
		  25, 14, 19,  9, 13,  8,  7,  6
	  };

    const uint64_t debruijn64 = UINT64_C(0x03f79d71b4cb0a89);
    return index64[((bb & -static_cast<int64_t>(bb)) * debruijn64) >> 58];

#endif
  }

  inline Bitboard ResetLSB(Bitboard b)
  {
    return b & (b - 1);
  }
}
