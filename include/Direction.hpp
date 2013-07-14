#ifndef INCLUDE_DIRECTION_HPP_
#define INCLUDE_DIRECTION_HPP_

namespace Pgn
{
  enum class Direction : unsigned char
  {
    NONE,
    HORIZONTAL,
    VERTICAL,
    DIAGONAL,
    ANTI_DIAGONAL
  };
}

#endif
