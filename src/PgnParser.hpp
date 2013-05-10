#ifndef INCLUDE_PGN_PARSER_HPP_
#define INCLUDE_PGN_PARSER_HPP_

#include <memory>

#include "PgnTokenizer.hpp"
#include "PgnToken.hpp"
#include "PgnGame.hpp"
#include "PgnVariation.hpp"
#include "PgnMove.hpp"

namespace PgnParser
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
        current_token_(new PgnToken(tokenizer_.get_next_token()))
    {};

    /*
     * This function parse and return a single game.
     */
    PgnGame parse_single_game();
  
  private:
    /*
     * Following are private helper functions
     */
    void read_next_token();
    bool eof() const;
    void check_unexpected_eof() const;
    void skip_expected_token(PgnTokenType type, const std::string& value);
    void check_expected_token_type(PgnTokenType type);
    void check_expected_token_value(const std::string& value);

    void parse_tags(PgnTags& tags);
    void parse_variation(unsigned int first_move_number, bool first_move_white, PgnVariation* variation);
    std::shared_ptr<PgnMove> parse_move();
  };
}

#endif // INCLUDE_PGN_PARSER_HPP_
