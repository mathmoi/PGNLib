/**
* @file Direction.hpp
*
* Contains the Direction enumeration.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/
#ifndef INCLUDE_DIRECTION_HPP_
#define INCLUDE_DIRECTION_HPP_

namespace m8db
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
