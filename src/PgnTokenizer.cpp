#include <cctype>
#include <cassert>

#include "../include/PgnTokenizer.hpp"
#include "../include/PgnToken.hpp"

namespace Pgn
{
  PgnTokenizer::PgnTokenizer(std::istream* ptr_is)
      : ptr_is_(ptr_is),
        current_line_(1)
  {
    ReadNextChar();

    // We need skip the white spaces so if the user call eof() we can return 
    // true or false.
    SkipWhiteSpaces();
  }

  void PgnTokenizer::ReadNextChar()
  {
    current_char_ = ptr_is_->good() ? static_cast<char>(ptr_is_->get()) : '\0';

    // If the charater we just read is a newline, we need to increment the line
    // counter.
    if (current_char_ == '\n')
    {
      ++current_line_;
    }
  }

  void PgnTokenizer::StoreCurrentCharReadNext()
  {
    current_value_ += current_char_;
    ReadNextChar();
  }

  void PgnTokenizer::SkipWhiteSpaces()
  {
    // There is 3 situation in wich we need to escape a character :
    //   1) If the character is a whitespace (comprised between '\0' and ' ')
    //   2) If the character is a '%' following a newline (This mean the whole 
    //      line will need to be escaped.
    //   3) The EOF character '\377'.
    while (current_char_ != '\0'
           && (current_char_ == '%'
               || (current_char_ > '\0' && current_char_ <= ' ')
               || current_char_ == '\377'))
    {
      // If the current character is a '%' we skip the whole line.
      if (current_char_ == '%')
      {
        while (current_char_ != '\0' 
               && current_char_ != '\n'
               && current_char_ != '\r')
        {
          ReadNextChar();
        } 
      }
      else
      {
        ReadNextChar();
      }
    }
  }

  void PgnTokenizer::CheckUnexpectedEof()
  {
    if (eof())
    {
      throw UnexpectedEofException();
    }
  }

  PgnToken PgnTokenizer::ReadWordToken()
  {
    assert(!eof());
    assert(std::isalpha(current_char_)); // The current character is a letter

    do {
      StoreCurrentCharReadNext();
    } while (std::isalpha(static_cast<unsigned char>(current_char_))
             || std::isdigit(current_char_)
             || current_char_ == '+'
             || current_char_ == '#'
             || current_char_ == '-'
             || current_char_ == '=');

    PgnToken token(WORD, current_value_);
    ResetCurrentValue();
    SkipWhiteSpaces();
    assert(token.type() == WORD);
    return token;
  }

  PgnToken PgnTokenizer::ReadStringToken()
  {
    assert(!eof());
    assert(current_char_ == '"'); // The current character is a string delimiter ('"').

    bool escape_next = false; // This will be set to true if we need to escape a character.

    ReadNextChar(); // We skip the quote
    while (!eof()
           && (current_char_ != '"' || escape_next))
    {
      // if the current_char_ is the escape character ('\'), we mark the next
      // character as escaped. If the next character is a quote it will prevent
      // the loop from terminating. If the next character is a backslash it
      // will be stored.
      if (!escape_next && current_char_ == '\\')
      {
        escape_next = true;
        ReadNextChar();
      }
      else
      {
        StoreCurrentCharReadNext();
        escape_next = false;
      }
    }

    CheckUnexpectedEof();

    ReadNextChar(); // We skip the closing quote

    PgnToken token(STRING, current_value_);
    ResetCurrentValue();
    SkipWhiteSpaces();
    return token;
  }

  PgnToken PgnTokenizer::ReadCommentToken()
  {
    assert(!eof());
    assert(current_char_ == '{' || current_char_ == ';');

    // We check if we read a remaining of line or a comment within braces.
    if (current_char_ == '{')
    {
      ReadNextChar(); // '{'
      while(!eof() && current_char_ != '}')
      {
        StoreCurrentCharReadNext();
      }

      CheckUnexpectedEof();
      ReadNextChar(); // '}'
    }
    else
    {
      ReadNextChar(); // ';'
      while (!eof() && current_char_ != '\n' && current_char_ != '\r')
      {
        StoreCurrentCharReadNext();
      }
    }

    PgnToken token(COMMENT, current_value_);
    ResetCurrentValue();
    SkipWhiteSpaces();
    return token;
  }

  PgnToken PgnTokenizer::ReadResultToken()
  {
    assert(std::isdigit(static_cast<unsigned char>(current_char_)) || current_char_ == '*' || current_char_ == '-' || current_char_ == '/');

    StoreCurrentCharReadNext();
    while (std::isdigit(static_cast<unsigned char>(current_char_)) || current_char_ == '*' || current_char_ == '-' || current_char_ == '/')
    {
      StoreCurrentCharReadNext();
    }

    PgnToken token(RESULT, current_value_);
    ResetCurrentValue();
    SkipWhiteSpaces();
    return token;
  }

  PgnToken PgnTokenizer::ReadNumberToken()
  {
    assert(std::isdigit(static_cast<unsigned char>(current_char_)));

    StoreCurrentCharReadNext();
    while (std::isdigit(static_cast<unsigned char>(current_char_)))
    {
      StoreCurrentCharReadNext();
    }

    PgnToken token(NUMBER, current_value_);
    ResetCurrentValue();
    SkipWhiteSpaces();
    return token;
  }

  PgnToken PgnTokenizer::ReadSymbolToken()
  {
    StoreCurrentCharReadNext();

    // If the first character is a dot en the next character is a dot we 
    // continue to read characters. This will allow us to threat multiples  
    // consecutives dots as a single symbol. This is necessary to 
    // differentiate dots from elipsis.
    while (current_value_[0] == '.' && current_char_ == '.')
    {
      StoreCurrentCharReadNext();
    }

    PgnToken token(SYMBOL, current_value_);
    ResetCurrentValue();
    SkipWhiteSpaces();
    return token;
  }

  PgnToken PgnTokenizer::GetNextToken()
  {
    if (this->eof())
    {
      throw EndOfStreamException();
    }

    if (std::isalpha(static_cast<unsigned char>(current_char_)))
    {
      return ReadWordToken();
    }

    if (current_char_ == '"')
    {
      return ReadStringToken();
    }

    if (current_char_ == '{'
        || current_char_ == ';')
    {
      return ReadCommentToken();
    }

    if (current_char_ == '*')
    {
      return ReadResultToken();
    }

    // At this point if the current_char_ is a digit there is two possibilities
    //  1) The token is a result, in wich case the next character is a '-' or a
    //      '/'.
    //  2) In other cases the token is a number
    if (std::isdigit(static_cast<unsigned char>(current_char_)))
    {
      if (ptr_is_->peek() == '-' || ptr_is_->peek() == '/')
      {
        return ReadResultToken();
      }
      else
      {
        return ReadNumberToken();
      }
    }

    return ReadSymbolToken();
  }
}
