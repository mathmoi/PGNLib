#ifndef INCLUDE_PGN_GAME_HPP_
#define INCLUDE_PGN_GAME_HPP_

#include <map>

#include "PgnVariation.hpp"

namespace PgnParser
{
  class PgnGame
  {
  public: 
    typedef std::map<std::string, std::string> TagsContainer;
  
  private:
    TagsContainer tags_;
    PgnVariation move_text_;

  public:
    inline PgnGame() {};

    /*
     * This function return a reference to the internal map object holding the
     * tags names and values. The client code can directly modify this object.
     *
     * We violate the encapsulations rules here, but it greatly simplify the
     * interface.
     */
    inline TagsContainer& get_tags() { return tags_; };

    /*
     * This function returns a reference to the internal move_text_ object.
     *
     * Again, we violate the encapsulation concept to simplify the interface.
     */
    inline PgnVariation& get_move_text() { return move_text_; };
  };
}

#endif // INCLUDE_PGN_GAME_HPP_
