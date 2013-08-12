#ifndef INCLUDE_PGN_NAG_HPP_
#define INCLUDE_PGN_NAG_HPP_

#include <cstdint>

#include "PgnMoveTextItem.hpp"

namespace PgnLib
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
  
  /**
   * Represent a Numerical Annotation Glyph (NAG) in a PGN game.
   *
   * Since the suffix annotations (!, !!, !?, ?!, ??, ?) must be transformed 
   * into NAG in the output format, they are also represented by a
   * corresponding PgnNag the parser convert them to PgnNag when the game is 
   * parsed.
   */
  class PgnNag : public PgnMoveTextItem
  {
  private:
    uint8_t nag_;

  public:
    /**
    * Construct a new nag with the specified value.
    * 
    * @param  nag   Value of the NAG.
    */
    PgnNag(uint8_t nag)
      : nag_(nag)
    {};

    /**
     * Creates a copy of the PgnNAG
     *
     * This function create a dynamically allocated copy of the item. The code
     * which calls the function must assume ownership of the allocated memory 
     * and is responsible for releasing it eventually.
     *
     * @return a pointer to a dynamically allocated copy of the object.
     */
    inline PgnMoveTextItem* Clone() const { return new PgnNag(nag_); };

    /** 
    * Get the value of the NAG.
    * 
    * @return  Value of the NAG
    */
    inline uint8_t nag() const { return nag_; };

    /**
     * Set the value of the NAG
     *
     * @param   nag   New value of the NAG
     */
    inline void set_nag(uint8_t nag) { nag_ = nag; };
  };
}

#endif // INCLUDE_PGN_NAG_HPP_
