#ifndef INCLUDE_PGN_PARSER_EXCEPTION_HPP
#define INCLUDE_PGN_PARSER_EXCEPTION_HPP

#include <stdexcept>
#include <cstdint>

namespace PgnLib
{
  /**
   * Base type for all the exception thrown by the PgnParser
   */
  class PgnParserException : public std::runtime_error
  {
  private:
    int32_t line_number_;

  public:
    /**
     * Constructor
     */
    inline PgnParserException(std::string what)
      : std::runtime_error(what),
        line_number_(-1) {};
    
    /**
     * Return the line number of the source stream that the parser was reading 
     * when it encountered a problem.
     *
     * If the source is at fault the error is probably on this line or near 
     * before it.
     *
     * @return  A line number
     */
    inline int32_t line_number() const { return line_number_; };

    /// @cond
    inline void set_line_number(int32_t line_number) { line_number_ = line_number; };
    /// @endcond
  };
}

#endif
