#ifndef INCLUDE_PGN_PARSER_HPP_
#define INCLUDE_PGN_PARSER_HPP_

#include <memory>

#include "PgnTokenizer.hpp"
#include "PgnToken.hpp"
#include "PgnGame.hpp"
#include "PgnVariation.hpp"
#include "PgnMove.hpp"
#include "PgnNag.hpp"
#include "PgnComment.hpp"
#include "Chessboard.hpp"

namespace Pgn
{
  class UnexpectedTokenException : public std::runtime_error
  {
  public:
    UnexpectedTokenException()
      : runtime_error("An unexpected token was found while parsing the pgn games.") {}
  };

  class PgnParser
  {
  private:
    PgnTokenizer tokenizer_;
    std::unique_ptr<PgnToken> current_token_;

  public:
    /*
     * Constructor of the class. It takes a pointer to an istream on wich 
     * it will read the games to parse.
     */
    inline PgnParser(std::istream* is)
      : tokenizer_(is),
        current_token_(new PgnToken(tokenizer_.GetNextToken()))
    {};

    /*
     * This function parse and return a single game.
     */
    PgnGame ParseSingleGame();

    /*
     * Indicate if the eof the stream is reached. If not, we should be able to 
     * read the next game with ParseSingleGame.
     */
    bool eof() const;
  
  private:
    /*
     * Following are private helper functions
     */
    void ReadNextToken();
    void CheckUnexpectedEof() const;
    void SkipExpectedToken(PgnTokenType type, const std::string& value);
    void CheckExpectedTokenType(PgnTokenType type);
    void CheckExpectedTokenValue(const std::string& value);

    void ParseTags(PgnTags& tags);
    void ParseVariation(Chessboard board, unsigned int first_move_number, bool first_move_white, PgnVariation* variation);
    std::shared_ptr<PgnMove> ParseMove(const Chessboard& board);
    std::shared_ptr<PgnNag> ParseNag();
    std::shared_ptr<PgnNag> ParseSuffixAnnotation();
    std::shared_ptr<PgnComment> ParseComment();
    PgnResult ParseResult();
  };
}

#endif // INCLUDE_PGN_PARSER_HPP_
