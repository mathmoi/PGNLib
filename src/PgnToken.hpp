#ifndef INCLUDE_PGN_TOKEN_HPP_
#define INCLUDE_PGN_TOKEN_HPP_

#include <string>

namespace PgnParser
{
  enum PgnTokenType
  {
    SYMBOL = 0,
    WORD,
    STRING,
    COMMENT,
    NUMBER,
    RESULT
  }

  class PgnToken
  {
  private:
    PgnTokenType m_type;
    std::string m_value;

  public:
    PgnToken(PgnTokenType type, std::string m_value)
    {
      m_type = type;
      m_value = value;
    }

    PgnTokenType get_type() const
    {
      return m_type;
    };

    const std::string& get_value() const
    {
      return m_value;
    };
  }
}

#endif // INCLUDE_PGN_TOKEN_HPP_
