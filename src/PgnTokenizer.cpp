#include <cctype>
#include <cassert>
#include <iostream> // TODO : Remove this

#include "PgnTokenizer.hpp"
#include "PgnToken.hpp"

namespace PgnParser
{
  PgnTokenizer::PgnTokenizer(std::istream* ptr_is)
      : ptr_is_(ptr_is)
  {
    current_char_ = ptr_is_->get();

    // We need skip the white spaces so if the user call eof() we can return 
    // true or false.
    skip_white_spaces();
  };

  void PgnTokenizer::read_next_char()
  {
    current_char_ = ptr_is_->good() ? ptr_is_->get() : '\0';
  }

  void PgnTokenizer::store_current_char_read_next()
  {
    current_value_ += current_char_;
    read_next_char();
  }

  void PgnTokenizer::skip_white_spaces()
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
          read_next_char();
        } 
      }
      else
      {
        read_next_char();
      }
    }
  }

  void PgnTokenizer::check_unexpected_eof()
  {
    if (eof())
    {
      throw UnexpectedEofException();
    }
  }

  PgnToken PgnTokenizer::read_word_token()
  {
    assert(!eof());
    assert(std::isalpha(current_char_)); // The current character is a letter

    do {
      store_current_char_read_next();
    } while (std::isalpha(current_char_)
             || std::isdigit(current_char_)
             || current_char_ == '+'
             || current_char_ == '#'
             || current_char_ == '-'
             || current_char_ == '=');

    PgnToken token(WORD, current_value_);
    reset_current_value();
    skip_white_spaces();
    return token;
  }

  PgnToken PgnTokenizer::read_string_token()
  {
    assert(!eof());
    assert(current_char_ == '"'); // The current character is a string delimiter ('"').

    bool escape_next = false; // This will be set to true if we need to escape a character.

    read_next_char(); // We skip the quote
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
        read_next_char();
      }
      else
      {
        store_current_char_read_next();
        escape_next = false;
      }
    }

    check_unexpected_eof();

    read_next_char(); // We skip the closing quote

    PgnToken token(STRING, current_value_);
    reset_current_value();
    skip_white_spaces();
    return token;
  }

  PgnToken PgnTokenizer::get_next_token()
  {
    if (this->eof())
    {
      throw EndOfStreamException();
    }

    if (std::isalpha(current_char_))
    {
      return read_word_token();
    }

    if (current_char_ == '"')
    {
      return read_string_token();
    }
  }
}
