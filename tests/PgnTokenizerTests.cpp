#include <string>
#include <sstream>
#include <fstream> // TODO : remove
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

    TEST(ReadCommentTest)
    {
      std::string str(" {Comment number one} \n  alloa ; Comment number two\n {Comment number three}");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.get_next_token();
      CHECK_EQUAL(token1.get_type(), COMMENT);
      CHECK_EQUAL(token1.get_value(), "Comment number one");

      PgnToken token2 = tokenizer.get_next_token();
      CHECK_EQUAL(token2.get_type(), WORD);
      CHECK_EQUAL(token2.get_value(), "alloa");

      PgnToken token3 = tokenizer.get_next_token();
      CHECK_EQUAL(token3.get_type(), COMMENT);
      CHECK_EQUAL(token3.get_value(), " Comment number two");
      
      PgnToken token4 = tokenizer.get_next_token();
      CHECK_EQUAL(token4.get_type(), COMMENT);
      CHECK_EQUAL(token4.get_value(), "Comment number three");
    }

    TEST(ReadResultTest)
    {
      std::string str("* 1-0 0-1 1/2-1/2");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.get_next_token();
      CHECK_EQUAL(token1.get_type(), RESULT);
      CHECK_EQUAL(token1.get_value(), "*");

      PgnToken token2 = tokenizer.get_next_token();
      CHECK_EQUAL(token2.get_type(), RESULT);
      CHECK_EQUAL(token2.get_value(), "1-0");

      PgnToken token3 = tokenizer.get_next_token();
      CHECK_EQUAL(token3.get_type(), RESULT);
      CHECK_EQUAL(token3.get_value(), "0-1");

      PgnToken token4 = tokenizer.get_next_token();
      CHECK_EQUAL(token4.get_type(), RESULT);
      CHECK_EQUAL(token4.get_value(), "1/2-1/2");
    }

    TEST(ReadNumberTest)
    {
      std::string str("1 236 3");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.get_next_token();
      CHECK_EQUAL(token1.get_type(), NUMBER);
      CHECK_EQUAL(token1.get_value(), "1");

      PgnToken token2 = tokenizer.get_next_token();
      CHECK_EQUAL(token2.get_type(), NUMBER);
      CHECK_EQUAL(token2.get_value(), "236");

      PgnToken token3 = tokenizer.get_next_token();
      CHECK_EQUAL(token3.get_type(), NUMBER);
      CHECK_EQUAL(token3.get_value(), "3");

    }

    TEST(ReadSymbolTest)
    {
      std::string str(". ... !?");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.get_next_token();
      CHECK_EQUAL(token1.get_type(), SYMBOL);
      CHECK_EQUAL(token1.get_value(), ".");

      PgnToken token2 = tokenizer.get_next_token();
      CHECK_EQUAL(token2.get_type(), SYMBOL);
      CHECK_EQUAL(token2.get_value(), "...");

      PgnToken token3 = tokenizer.get_next_token();
      CHECK_EQUAL(token3.get_type(), SYMBOL);
      CHECK_EQUAL(token3.get_value(), "!");

      PgnToken token4 = tokenizer.get_next_token();
      CHECK_EQUAL(token4.get_type(), SYMBOL);
      CHECK_EQUAL(token4.get_value(), "?");
    }

    /*TEST(tmp)
    {
      std::ifstream in("pgn/hard.pgn");
      
      PgnTokenizer tokenizer(&in);

      while (!tokenizer.eof())
      {
        PgnToken t = tokenizer.get_next_token();
        std::cout <<t.get_value() <<std::endl;
      }

      in.close();
    }*/
  }
}
