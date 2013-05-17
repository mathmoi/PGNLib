#ifndef INCLUDE_PGN_GAME_HPP_
#define INCLUDE_PGN_GAME_HPP_

#include <cstdint>

#include "PgnTags.hpp"
#include "PgnVariation.hpp"

namespace PgnParser
{
  enum class PgnResult : uint8_t
  {
    WHITE_WIN,
    BLACK_WIN,
    DRAW,
    UNKNOWN
  };

  class PgnGame : public PgnVariation
  {
  private:
    PgnTags tags_;
    PgnResult result_;


  public:
    inline PgnGame() 
      : result_(PgnResult::UNKNOWN) {};

    /*
     * This function return a reference to the internal map object holding the
     * tags names and values. The client code can directly modify this object.
     */
    inline PgnTags& tags() { return tags_; };

    inline PgnResult result() const { return result_; };
    inline void set_result(PgnResult result) { result_ = result; };
  };
}

#endif // INCLUDE_PGN_GAME_HPP_
