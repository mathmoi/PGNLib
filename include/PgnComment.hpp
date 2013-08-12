#ifndef INCLUDE_PGN_COMMENT_HPP_
#define INCLUDE_PGN_COMMENT_HPP_

#include <string>

namespace PgnLib
{
  /**
   * Represent a comment in a PGN game's movetext.
   */
  class PgnComment : public PgnMoveTextItem
  {
  private:
    std::string comment_;

  public:
    /**
     * Construct a new comment.
     *
     * @param   comment   Text of the new comment.
     */
    inline PgnComment(const std::string& comment)
      : comment_(comment) {};

    /**
     * Creates a copy of the PgnComment
     *
     * This function create a dynamically allocated copy of the item. The code
     * which calls the function must assume ownership of the allocated memory 
     * and is responsible for releasing it eventually.
     *
     * @return a pointer to a dynamically allocated copy of the object.
     */
    inline PgnMoveTextItem* Clone() const { return new PgnComment(comment_); };

    /**
     * Get the comment's text.
     *
     * @return    The comment's text
     */
    inline const std::string& comment() const { return comment_; };

    /**
     * Set the comment's text
     *
     * @param   comment   New comment's text.
     */
    inline void set_comment(const std::string& comment) { comment_ = comment; };
  };
}

#endif // INCLUDE_PGN_COMMENT_HPP_
