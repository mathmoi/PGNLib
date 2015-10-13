/**
* @file PgnGame.hpp
*
* Contains the PgnGame class.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/
#ifndef INCLUDE_PGN_GAME_HPP_
#define INCLUDE_PGN_GAME_HPP_

#include <cstdint>

#include "PgnTags.hpp"
#include "PgnVariation.hpp"

namespace m8db
{
  /**
   * Enum type used to store the result of a PgnGame.
   */
  enum class PgnResult : uint8_t
  {
    WHITE_WIN,  ///< The player playing the white pieces wins
    BLACK_WIN,  ///< The player playing the black pieces wins
    DRAW,       ///< The game is draw
    UNKNOWN     ///< The result is unkown
  };

  /**
   * Represent a single chess game in a PGN file.
   *
   * PgnGame inherits from PgnVariation since the Movetext (the part of a PGN 
   * game with the move, variation, comments et annotation) is considered a 
   * variation (the main variation).
   *
   * The PgnGame object is returned by the PgnParser's ParseSingleGame 
   * function. It contains all informations found in the PGN file for a single 
   * game.
   *
   * You can access the tags names and values by using the `tags()` property.
   * You can access the moves, variations, comments and annotation using the
   * inherited PgnVariation interface. Finaly, you can get the game's result 
   * using the `result()` property.
   */
  class PgnGame : public PgnVariation
  {
  private:
    PgnTags tags_;
    PgnResult result_;

  public:
    /**
     * Constructor
     */
    inline PgnGame() 
      : result_(PgnResult::UNKNOWN) {};

    /**
     * Returns a reference to the internal map object holding the tags names 
     * and values.
     *
     * The client code can directly modify this object.
     *
     * @return  reference to the game's PgnTags object.
     */
    inline PgnTags& tags() { return tags_; };
    inline const PgnTags& tags() const { return tags_; };

    /**
     * Get the result of the game
     *
     * @return The result of the game
     */
    inline PgnResult result() const { return result_; };

    /**
     * Set the result of the game
     *
     * @param   result  The new result of the game
     */
    inline void set_result(PgnResult result) { result_ = result; };
  };
}

#endif // INCLUDE_PGN_GAME_HPP_
