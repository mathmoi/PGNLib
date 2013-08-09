#ifndef INCLUDE_PGN_PARSER_EXCEPTION_HPP
#define INCLUDE_PGN_PARSER_EXCEPTION_HPP

#include <stdexcept>
#include <cstdint>

namespace PgnLib
{
  class PgnParserException : public std::runtime_error
  {
  private:
    int32_t line_number_;

  public:
    inline PgnParserException(std::string what)
      : std::runtime_error(what),
        line_number_(-1) {};

    inline int32_t line_number() const { return line_number_; };
    inline void set_line_number(int32_t line_number) { line_number_ = line_number; };
  };
}

#endif
