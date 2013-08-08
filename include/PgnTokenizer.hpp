#ifndef INCLUDE_PGN_TOKENIZER_HPP_
#define INCLUDE_PGN_TOKENIZER_HPP_

#include <istream>
#include <string>

#include "PgnToken.hpp"
#include "PgnParserException.hpp"

namespace Pgn
{
  /*
   * Exception class used when a token is requested but the end of the stream 
   * is reached.
   */
  class EndOfStreamException : public PgnParserException
  {
  public:
    EndOfStreamException()
      : PgnParserException("No more data on the stream to generate a token.") {}
  };

  /*
   * Exception class used when we reach the end of the stream while we are 
   * still especting characters. This usually mean there is an error in the 
   * PGN file.
   */
  class UnexpectedEofException : public PgnParserException
  {
  public:
    UnexpectedEofException()
      : PgnParserException("Unexpected end of stream while parsing pgn games.") {}
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

    // Current line number
    uint64_t current_line_;
    
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
    PgnToken GetNextToken();

    /*
     * This function indicate if there is still tokens to read on the stream. 
     * It should be called before get_next_token to verify if we reached the 
     * end of the stream.
     */
    inline bool eof() { return current_char_ == '\0'; };

    inline uint64_t current_line() const { return current_line_; };

  private:
    void SkipWhiteSpaces();
    void ReadNextChar();
    void StoreCurrentCharReadNext();
    inline void ResetCurrentValue() { current_value_.clear(); };
    void CheckUnexpectedEof();
    PgnToken ReadWordToken();
    PgnToken ReadStringToken();
    PgnToken ReadCommentToken();
    PgnToken ReadResultToken();
    PgnToken ReadNumberToken();
    PgnToken ReadSymbolToken();
  };
}

#endif // INCLUDE_PGN_TOKENIZER_HPP_
