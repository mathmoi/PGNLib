#ifndef INCLUDE_PGN_TOKENIZER_HPP_
#define INCLUDE_PGN_TOKENIZER_HPP_

#include <istream>
#include <string>
#include <stdexcept>
#include <iostream> // TODO: remove

#include "PgnToken.hpp"

namespace PgnParser
{
  /*
   * Exception class used when a token is requested but the end of the stream 
   * is reached.
   */
  class EndOfStreamException : public std::runtime_error
  {
  public:
    EndOfStreamException()
      : runtime_error("No more data on the stream to generate a token.") {}
  };

  /*
   * Exception class used when we reach the end of the stream while we are 
   * still especting characters. This usually mean there is an error in the 
   * PGN file.
   */
  class UnexpectedEofException : public std::runtime_error
  {
  public:
    UnexpectedEofException()
      : runtime_error("Unexpected end of stream while parsing pgn games.") {}
  };

  /*
   * The PgnTokenizer class is used to isolate every token from a PGN games
   * file. It's interface allow the PgnParser to use it to get each tokens
   * one at a time.
   */
  class PgnTokenizer
  {
  private:
    // Pointer to the stream on which we read the games.
    std::istream* ptr_is_;

    // The value we are currently building for the next token.
    std::string current_value_;

    // The next character to use. This comes from is_ and we should use 
    // read_next_char() to replace it with a new one.
    char current_char_;
    
  public:
    /*
     * Constructor of the class. Takes a istream as an input. This istream
     * will be used to read the PGN Games and generate the tokens. It can
     * be an ifstream, an istringstream or any other istream.
     */
    PgnTokenizer(std::istream* ptr_is);

    /*
     * Generates and return the next token. If there is no more tokens to 
     * return an EndOfStreamException is thrown.
     */
    PgnToken get_next_token();

    /*
     * This function indicate if there is still tokens to read on the stream. 
     * It should be called before get_next_token to verify if we reached the 
     * end of the stream.
     */
    inline bool eof() { return current_char_ == '\0'; };

  private:
    void skip_white_spaces();
    void read_next_char();
    void store_current_char_read_next();
    inline void reset_current_value() { current_value_.clear(); };
    void check_unexpected_eof();
    PgnToken read_word_token();
    PgnToken read_string_token();
    PgnToken read_comment_token();
    PgnToken read_result_token();
    PgnToken read_number_token();
    PgnToken read_symbol_token();
  };
}

#endif // INCLUDE_PGN_TOKENIZER_HPP_
