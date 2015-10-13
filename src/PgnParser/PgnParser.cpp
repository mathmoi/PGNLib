#include <cassert>

#include "PgnParser.hpp"
#include "SANParser.hpp"

namespace m8db
{
  std::map<std::string, PgnResult> CreateResultMap()
  {
    std::map<std::string, PgnResult> map;
    map["1-0"] = PgnResult::WHITE_WIN;
    map["1-O"] = PgnResult::WHITE_WIN;
    map["0-1"] = PgnResult::BLACK_WIN;
    map["O-1"] = PgnResult::BLACK_WIN;
    map["1/2-1/2"] = PgnResult::DRAW;
    map["*"] = PgnResult::UNKNOWN;
    return map;
  }
  const std::map<std::string, PgnResult> RESULT_MAP = CreateResultMap();


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

  PgnMove* PgnParser::ParseMove(const Chessboard& board)
  {
    assert(current_token_->type() == WORD);

    PgnMove* move = new PgnMove(ParseSanMove(board, current_token_->value()));
    ReadNextToken();

    return move;
  }

  PgnNag* PgnParser::ParseNag()
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

    PgnNag* nag = new PgnNag(static_cast<uint8_t>(n));
    ReadNextToken();
    return nag;
  }

  PgnNag* PgnParser::ParseSuffixAnnotation()
  {
    assert(current_token_->type() == SYMBOL);
    assert(current_token_->value() == "!" || current_token_->value() == "?");

    PgnNag* nag;

    if (current_token_->value() == "!")
    {
      ReadNextToken();
      if (current_token_->type() == SYMBOL && current_token_->value() == "!")
      {
        nag = new PgnNag(static_cast<uint8_t>(NAG::VERY_GOOD_MOVE));
        ReadNextToken();
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "?")
      {
        nag = new PgnNag(static_cast<uint8_t>(NAG::SPECULATIVE_MOVE));
        ReadNextToken();
      }
      else
      {
        nag = new PgnNag(static_cast<uint8_t>(NAG::GOOD_MOVE));
      }
    }
    else if (current_token_->value() == "?")
    {
      ReadNextToken();
      if (current_token_->type() == SYMBOL && current_token_->value() == "!")
      {
        nag = new PgnNag(static_cast<uint8_t>(NAG::QUESTIONABLE_MOVE));
        ReadNextToken();
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "?")
      {
        nag = new PgnNag(static_cast<uint8_t>(NAG::VERY_POOR_MOVE));
        ReadNextToken();
      }
      else
      {
        nag = new PgnNag(static_cast<uint8_t>(NAG::POOR_MOVE));
      }
    }
    else
    {
      throw UnexpectedTokenException();
    }
    return nag;
  }

  PgnComment* PgnParser::ParseComment()
  {
    assert(current_token_->type() == COMMENT);

    PgnComment* comment = new PgnComment(current_token_->value().c_str());
    ReadNextToken();
    return comment;
  }

  // This function which parse a variation takes a pointer to a PgnVariation
  // object instead of creating the variation itself. This allow the client
  // code to pass a pointer to a PgnVariation or a downcasted pointer to a
  // PgnGame.
  void PgnParser::ParseVariation(Chessboard board, unsigned int first_move_number, bool first_move_white, PgnVariation* variation)
  {
    bool is_sub_variation = false;
         
    // This will contains the number of move parsed in this variation.
    unsigned int number_move_parsed = 0;

    // This contains the last move parsed. The last move is not added to the 
    // board right away, because the board position might still need to be 
    // passed to sub variations.
    PgnMove* last_move_parsed = 0;

    // If the current token is an opening parenthesis, we are parsing a sub 
    // variation. We take note and skip the parenthesis.
    if (current_token_->type() == SYMBOL
        && current_token_->value() == "(")
    {
      ReadNextToken(); // skip '('
      is_sub_variation = true;   
    }

    // While we are not at the end of the source, we are not at a result token 
    // and we are not at a closing parenthesis token, we continue to parse the 
    // variation.
    while (!eof()
           && current_token_->type() != RESULT
           && current_token_->value() != ")")
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
        // If there was a move parsed not yet played on the board we make it.
        if (last_move_parsed)
        {
          board.MakeMove(last_move_parsed->from(), last_move_parsed->to(), last_move_parsed->promotion_piece_type());
        }

        // If the current token is a word we parse it as a move.
        PgnMove* move = ParseMove(board);
        variation->push_back(move);
        ++number_move_parsed;
        
        last_move_parsed = move;
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
        PgnMoveTextItem* item = ParseNag();
        variation->push_back(item);
      }
      else if (current_token_->type() == SYMBOL
               && (current_token_->value()[0] == '!' || current_token_->value()[0] == '?'))
      {
        // If the current token is a '!' or a '?', we parse it as a suffix annotation
        PgnMoveTextItem* item = ParseSuffixAnnotation();
        variation->push_back(item);
      }
      else if (current_token_->type() == SYMBOL && current_token_->value() == "(")
      {
        // If the current token is an opening parenthesis we parse a 
        // sub variation.
        PgnVariation* sub_variation = new PgnVariation;
        unsigned int first_move_index = first_move_number * 2 - (first_move_white ? 1 : 0);
        unsigned int next_move_index = first_move_index + number_move_parsed - 1;
        unsigned int next_move_number = (next_move_index + 1) / 2;
        bool next_move_white = (next_move_index % 2) != 0;
        ParseVariation(board, next_move_number, next_move_white, sub_variation);

        variation->push_back(sub_variation);
      }
      else if (current_token_->type() == COMMENT)
      {
        PgnMoveTextItem* item = ParseComment();
        variation->push_back(item);
      }
      else if (current_token_->type() == SYMBOL)
      {
        // If there is another (unrecognised) symbol we skip it and hope for 
        // the best. In some case this will allow the parser to accept files 
        // that would be otherwise invalid.
        ReadNextToken();
      }
      else
      {
        throw UnexpectedTokenException();
      }
    }

    // If it was a sub variation we expect to read a closing parenthesis
    if (is_sub_variation)
    {
      SkipExpectedToken(SYMBOL, ")");
    }
  }

  PgnResult PgnParser::ParseResult()
  {
    CheckExpectedTokenType(RESULT);

    PgnResult result = PgnResult::UNKNOWN;
    try
    {
      result = RESULT_MAP.at(current_token_->value());
    }
    catch (std::out_of_range ex)
    {
      throw UnexpectedTokenException();
    }

    ReadNextToken();
    return result;
  }

  PgnGame PgnParser::ParseSingleGame()
  {
    PgnGame game;

    try
    {
      CheckUnexpectedEof();

      // We parse the tags
      ParseTags(game.tags());

      // We parse the moves
      Chessboard board;
      ParseVariation(board, 1, true, &game);

      game.set_result(ParseResult());
    }
    catch (PgnParserException ex)
    {
      ex.set_line_number(tokenizer_.current_line());
      throw ex;
    }

    return game;
  }
}
