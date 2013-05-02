#include <string>
#include <sstream>
#include <iostream> // TODO : remove

#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/PgnTokenizer.hpp"

namespace PgnParser
{
  SUITE(PgnTokenizerTests)
  {
    TEST(ReadWordTokens)
    {
      std::string str("   Bonjour le\t    \r \n  monde \r\n\t   ");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.get_next_token();
      CHECK_EQUAL(token1.get_type(), WORD);
      CHECK_EQUAL(token1.get_value(), "Bonjour");

      PgnToken token2 = tokenizer.get_next_token();
      CHECK_EQUAL(token2.get_type(), WORD);
      CHECK_EQUAL(token2.get_value(), "le");

      PgnToken token3 = tokenizer.get_next_token();
      CHECK_EQUAL(token3.get_type(), WORD);
      CHECK_EQUAL(token3.get_value(), "monde");

      CHECK(!is.good());
      CHECK(tokenizer.eof());
    }

    TEST(ReadStringTest)
    {
      std::string str(" \"Bonjour le monde\" \"Comment \\\\allez \\\"vous\\\"?\"  ");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.get_next_token();
      CHECK_EQUAL(token1.get_type(), STRING);
      CHECK_EQUAL(token1.get_value(), "Bonjour le monde");

      PgnToken token2 = tokenizer.get_next_token();
      CHECK_EQUAL(token2.get_type(), STRING);
      CHECK_EQUAL(token2.get_value(), "Comment \\allez \"vous\"?");

      CHECK(!is.good());
      CHECK(tokenizer.eof());
    }
  }
}
