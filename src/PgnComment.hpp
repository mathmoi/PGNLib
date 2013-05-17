#ifndef INCLUDE_PGN_COMMENT_HPP_
#define INCLUDE_PGN_COMMENT_HPP_

#include <string>

namespace PgnParser
{
  class PgnComment : public PgnMoveTextItem
  {
  private:
    std::string comment_;

  public:
    inline PgnComment(const std::string& comment)
      : comment_(comment) {};

    inline const std::string& comment() const { return comment_; };
    inline void set_comment(const std::string& comment) { comment_ = comment; };
  };
}

#endif // INCLUDE_PGN_COMMENT_HPP_
