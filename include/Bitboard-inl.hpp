namespace Pgn
{
  inline unsigned int BitSearch(Bitboard bb)
  {
#if defined(__GNUC__) && defined(__LP64__)
    asm ("bsfq %0, %0" : "=r" (bb) : "0" (bb));
    return static_cast<unsigned int>(bb);

#elif defined(_MSC_VER) && defined(_WIN64)
    int index = -1;
    _BitScanForward64(&index, bb);
    return index;

#else
    const boost::uint64_t debruijn64 = UINT64_C(0x07EDD5E59A4E28C2);
    return index64[((bb & -static_cast<boost::int64_t>(bb)) * debruijn64) >> 58];

#endif
  }

  inline Bitboard ResetLSB(Bitboard b)
  {
    return b & (b - 1);
  }
}
