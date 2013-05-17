#include <cassert>

#include "PgnParser.hpp"

namespace PgnParser
{
  void PgnParser::ReadNextToken()
  {
    if (tokenizer_.eof())
    {
      current_token_.reset();
    }
    else
    {
      current_token_.reset(new PgnToken(tokenizer_.GetNextToken()));
    }
  }

  bool PgnParser::eof() const
  {
    return !current_token_;
  }

  void PgnParser::CheckUnexpectedEof() const
  {
    if (eof())
    {
      throw UnexpectedEofException();
    }
  }

  void PgnParser::SkipExpectedToken(PgnTokenType type, const std::string& value)
  {
    CheckUnexpectedEof();

    if (current_token_->type() != type
        || current_token_->value() != value)
    {
      throw UnexpectedTokenException();
    }

    ReadNextToken();
  }

  void PgnParser::CheckExpectedTokenType(PgnTokenType type)
  {
    CheckUnexpectedEof();
    if (current_token_->type() != type)
    {
      throw UnexpectedTokenException();
    }
  }

  void PgnParser::CheckExpectedTokenValue(const std::string& value)
  {
    CheckUnexpectedEof();
    if (current_token_->value() != value)
    {
      throw UnexpectedTokenException();
    }
  }

  void PgnParser::ParseTags(PgnTags& tags)
  {
    while (current_token_
           && current_token_->type() == SYMBOL
           && current_token_->value() == "[")
    {
      ReadNextToken(); // Skip '['
      
      // The next token should be a word and this word will be the tag name.
      CheckExpectedTokenType(WORD);
      std::string name(current_token_->value());
      ReadNextToken();

      // The next token should be a string. This string is the tag value.
      CheckExpectedTokenType(STRING);
      std::string value(current_token_->value());
      ReadNextToken();

      // The next token should be a closing bracket. We skip it.
      SkipExpectedToken(SYMBOL, "]");

      tags[name] = value;
    }
  }

  std::shared_ptr<PgnMove> PgnParser::ParseMove()
  {
    assert(current_token_->type() == WORD);

    // When this function is called we simply need to create a PgnMove with 
    // the current (WORD) token.
    std::shared_ptr<PgnMove> move(new PgnMove(current_token_->value()));
    ReadNextToken();
    return move;
  }

  std::shared_ptr<PgnNag> PgnParser::ParseNag()
  {
    SkipExpectedToken(SYMBOL, "$");
    CheckExpectedTokenType(NUMBER);
    unsigned long n;
    try
    {
      n = std::stoul(current_token_->value());
    }
    catch (std::invalid_argument ex)
    {
      throw UnexpectedTokenException();
    }

    // If the number is greater than 255 we throw an exception.
    if (n > 255)
    {
      throw UnexpectedTokenException();
    }

    std::shared_ptr<PgnNag> nag(new PgnNag(n));
    ReadNextToken();
    return nag;
  }

  std::shared_ptr<PgnNag> PgnParser::ParseSuffixAnnotation()
  {
    static const std::map<std::string, NAG> ANNOTATION_MAP = 
    {
      {"!", NAG::GOOD_MOVE},
      {"?", NAG::POOR_MOVE},
      {"!!", NAG::VERY_GOOD_MOVE},
      {"??", NAG::VERY_POOR_MOVE},
      {"!?", NAG::SPECULATIVE_MOVE},
      {"?!", NAG::QUESTIONABLE_MOVE}
    };

    std::shared_ptr<PgnNag> nag;

    if (current_token_->value() == "!")
    {
      ReadNextToken();
      if (current_token_->type() == SYMBOL && current_token_->value() == "!")
      {
        nag.reset(new PgnNag(static_cast<uint8_t>(NAG::VERY_GOOD_MOVE)));
        ReadNextToken();
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "?")
      {
        nag.reset(new PgnNag(static_cast<uint8_t>(NAG::SPECULATIVE_MOVE)));
        ReadNextToken();
      }
      else
      {
        nag.reset(new PgnNag(static_cast<uint8_t>(NAG::GOOD_MOVE)));
      }
    }
    else if (current_token_->value() == "?")
    {
      ReadNextToken();
      if (current_token_->type() == SYMBOL && current_token_->value() == "!")
      {
        nag.reset(new PgnNag(static_cast<uint8_t>(NAG::QUESTIONABLE_MOVE)));
        ReadNextToken();
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "?")
      {
        nag.reset(new PgnNag(static_cast<uint8_t>(NAG::VERY_POOR_MOVE)));
        ReadNextToken();
      }
      else
      {
        nag.reset(new PgnNag(static_cast<uint8_t>(NAG::POOR_MOVE)));
      }
    }
    else
    {
      throw UnexpectedTokenException();
    }
    return nag;
  }

  // This function which parse a variation takes a pointer to a PgnVariation
  // object instead of creating the variation itself. This allow the client
  // code to pass a pointer to a PgnVariation or a downcasted pointer to a
  // PgnGame.
  void PgnParser::ParseVariation(unsigned int first_move_number, bool first_move_white, PgnVariation* variation)
  {
    //bool is_sub_variation = false;
         
    // This will contains the number of move parsed in this variation.
    unsigned int number_move_parsed = 0;

    // If the current token is an opening parenthesis, we are parsing a sub 
    // variation. We take note and skip the parenthesis.
    if (current_token_->type() == SYMBOL
        && current_token_->value() == "(")
    {
      ReadNextToken(); // skip '('
      //is_sub_variation = true;   
    }

    // While we are not at the end of the source, we are not at a result token 
    // and we are not at a closing parenthesis token, we continue to parse the 
    // variation.
    while (!eof()
           && current_token_->type() != RESULT
           && current_token_->value() != "(")
    {
      // If the current token is a number and we haven't parsed any move yet, 
      // we use this number as our first move number.
      if (current_token_->type() == NUMBER)
      {
        if (number_move_parsed == 0)
        {
          variation->set_first_move_number(std::stoi(current_token_->value().c_str()));
          variation->set_first_move_white(true);
        }
        ReadNextToken();
      }
      else if (current_token_->type() == WORD)
      {
        // If the current token is a word we parse it as a move.
        std::shared_ptr<PgnMoveTextItem> item = ParseMove();
        variation->push_back(item);
        ++number_move_parsed;
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == ".")
      {
        // We skip over single dots
        ReadNextToken();
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "...")
      {
        // If the current token is an elipsis and we have not parse any move 
        // yet, this elipsis indicate that the first move is a black move. 
        // Otherwise, we ignore the elipsis and hope for the best.
        if (number_move_parsed == 0)
        {
          variation->set_first_move_white(false);
        }
        ReadNextToken();
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "$")
      {
        // If the current token is a dollar sign, we parse a NAG.
        std::shared_ptr<PgnMoveTextItem> item = ParseNag();
        variation->push_back(item);
      }
      else if (current_token_->type() == SYMBOL
               && (current_token_->value()[0] == '!' || current_token_->value()[0] == '?'))
      {
        // If the current token is a '!' or a '?', we parse it as a suffix annotation
        std::shared_ptr<PgnMoveTextItem> item = ParseSuffixAnnotation();
        variation->push_back(item);
      }
      else
      {
        // TODO : Do something instead of burnign th tokens.
        ReadNextToken();
      }

    }
  }

  PgnGame PgnParser::ParseSingleGame()
  {
    PgnGame game;

    CheckUnexpectedEof();

    // We parse the tags
    ParseTags(game.tags());

    // We parse the moves
    ParseVariation(1, true, &game);

    return game;
  }
}
