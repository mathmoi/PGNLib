#ifndef INCLUDE_PGN_GAME_HPP_
#define INCLUDE_PGN_GAME_HPP_

#include "PgnTags.hpp"
#include "PgnVariation.hpp"

namespace PgnParser
{
  class PgnGame : public PgnVariation
  {
  public: 
    typedef std::map<std::string, std::string> TagsContainer;
  
  private:
    PgnTags tags_;

  public:
    inline PgnGame() {};

    /*
     * This function return a reference to the internal map object holding the
     * tags names and values. The client code can directly modify this object.
     */
    inline PgnTags& tags() { return tags_; };
  };
}

#endif // INCLUDE_PGN_GAME_HPP_
