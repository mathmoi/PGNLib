#ifndef INCLUDE_PGN_NAG_HPP_
#define INCLUDE_PGN_NAG_HPP_

#include <cstdint>

#include "PgnMoveTextItem.hpp"

namespace PgnParser
{
  enum class NAG : uint8_t
  {
    NULL_ANNOTATION = 0,
    GOOD_MOVE,            // !
    POOR_MOVE,            // ?
    VERY_GOOD_MOVE,       // !!
    VERY_POOR_MOVE,       // ??
    SPECULATIVE_MOVE,     // !?
    QUESTIONABLE_MOVE     // ?!
  };

  class PgnNag : public PgnMoveTextItem
  {
  private:
    uint8_t nag_;

  public:
    PgnNag(uint8_t nag)
      : nag_(nag)
    {};

    inline uint8_t nag() const { return nag_; };
    inline void set_nag(uint8_t nag) { nag_ = nag; };
  };
}

#endif // INCLUDE_PGN_NAG_HPP_
