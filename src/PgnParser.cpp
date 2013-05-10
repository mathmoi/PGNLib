#include <cassert>

#include "PgnParser.hpp"

namespace PgnParser
{
  void PgnParser::read_next_token()
  {
    if (tokenizer_.eof())
    {
      current_token_.reset();
    }
    else
    {
      current_token_.reset(new PgnToken(tokenizer_.get_next_token()));
    }
  }

  bool PgnParser::eof() const
  {
    return !current_token_;
  }

  void PgnParser::check_unexpected_eof() const
  {
    if (eof())
    {
      throw UnexpectedEofException();
    }
  }

  void PgnParser::skip_expected_token(PgnTokenType type, const std::string& value)
  {
    check_unexpected_eof();

    if (current_token_->get_type() != type
        || current_token_->get_value() != value)
    {
      throw UnexpectedTokenException();
    }

    read_next_token();
  }

  void PgnParser::check_expected_token_type(PgnTokenType type)
  {
    check_unexpected_eof();
    if (current_token_->get_type() != type)
    {
      throw UnexpectedTokenException();
    }
  }

  void PgnParser::check_expected_token_value(const std::string& value)
  {
    check_unexpected_eof();
    if (current_token_->get_value() != value)
    {
      throw UnexpectedTokenException();
    }
  }

  void PgnParser::parse_tags(PgnTags& tags)
  {
    while (current_token_
           && current_token_->get_type() == SYMBOL
           && current_token_->get_value() == "[")
    {
      read_next_token(); // Skip '['
      
      // The next token should be a word and this word will be the tag name.
      check_expected_token_type(WORD);
      std::string name(current_token_->get_value());
      read_next_token();

      // The next token should be a string. This string is the tag value.
      check_expected_token_type(STRING);
      std::string value(current_token_->get_value());
      read_next_token();

      // The next token should be a closing bracket. We skip it.
      skip_expected_token(SYMBOL, "]");

      tags[name] = value;
    }
  }

  std::shared_ptr<PgnMove> PgnParser::parse_move()
  {
    assert(current_token_->get_type() == WORD);

    // When this function is called we simply need to create a PgnMove with 
    // the current (WORD) token.
    std::shared_ptr<PgnMove> move(new PgnMove(current_token_->get_value()));
    read_next_token();
    return move;
  }

  // This function which parse a variation takes a pointer to a PgnVariation
  // object instead of creating the variation itself. This allow the client
  // code to pass a pointer to a PgnVariation or a downcasted pointer to a
  // PgnGame.
  void PgnParser::parse_variation(unsigned int first_move_number, bool first_move_white, PgnVariation* variation)
  {
    //bool is_sub_variation = false;
         
    // This will contains the number of move parsed in this variation.
    //unsigned int number_move_parsed = 0;

    // If the current token is an opening parenthesis, we are parsing a sub 
    // variation. We take note and skip the parenthesis.
    if (current_token_->get_type() == SYMBOL
        && current_token_->get_value() == "(")
    {
      read_next_token(); // skip '('
      //is_sub_variation = true;   
    }

    // While we are not at the end of the source, we are not at a result token 
    // and we are not at a closing parenthesis token, we continue to parse the 
    // variation.
    while (!eof()
           && current_token_->get_type() != RESULT
           && current_token_->get_value() != "(")
    {
      // If the current token is a number and we haven't parsed any move yet, 
      // we use this number as our first move number.
      if (current_token_->get_type() == NUMBER)
      {
        // TODO : implement this
        read_next_token();
      }
      else if (current_token_->get_type() == WORD)
      {
        // If the current token is a word we parse it as a move.
        std::shared_ptr<PgnMoveTextItem> item = parse_move();
        variation->push_back(item);
      }
      else
      {
        // TODO : Do something instead of burnign th tokens.
        read_next_token();
      }

    }
  }

  PgnGame PgnParser::parse_single_game()
  {
    PgnGame game;

    check_unexpected_eof();

    // We parse the tags
    parse_tags(game.tags());

    // We parse the moves
    parse_variation(1, true, &game);

    return game;
  }
}
