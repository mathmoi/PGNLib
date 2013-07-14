#include <string>
#include <sstream>

#include <UnitTest++.h>
#include <PgnTokenizer.hpp>

namespace Pgn
{
  SUITE(PgnTokenizerTests)
  {
    TEST(ReadWordTokens)
    {
      std::string str("   Bonjour le\t    \r \n  monde \r\n\t   ");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.GetNextToken();
      CHECK_EQUAL(token1.type(), WORD);
      CHECK_EQUAL(token1.value(), "Bonjour");

      PgnToken token2 = tokenizer.GetNextToken();
      CHECK_EQUAL(token2.type(), WORD);
      CHECK_EQUAL(token2.value(), "le");

      PgnToken token3 = tokenizer.GetNextToken();
      CHECK_EQUAL(token3.type(), WORD);
      CHECK_EQUAL(token3.value(), "monde");

      CHECK(!is.good());
      CHECK(tokenizer.eof());
    }

    TEST(ReadStringTest)
    {
      std::string str(" \"Bonjour le monde\" \"Comment \\\\allez \\\"vous\\\"?\"  ");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.GetNextToken();
      CHECK_EQUAL(token1.type(), STRING);
      CHECK_EQUAL(token1.value(), "Bonjour le monde");

      PgnToken token2 = tokenizer.GetNextToken();
      CHECK_EQUAL(token2.type(), STRING);
      CHECK_EQUAL(token2.value(), "Comment \\allez \"vous\"?");

      CHECK(!is.good());
      CHECK(tokenizer.eof());
    }

    TEST(ReadCommentTest)
    {
      std::string str(" {Comment number one} \n  alloa ; Comment number two\n {Comment number three}");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.GetNextToken();
      CHECK_EQUAL(token1.type(), COMMENT);
      CHECK_EQUAL(token1.value(), "Comment number one");

      PgnToken token2 = tokenizer.GetNextToken();
      CHECK_EQUAL(token2.type(), WORD);
      CHECK_EQUAL(token2.value(), "alloa");

      PgnToken token3 = tokenizer.GetNextToken();
      CHECK_EQUAL(token3.type(), COMMENT);
      CHECK_EQUAL(token3.value(), " Comment number two");
      
      PgnToken token4 = tokenizer.GetNextToken();
      CHECK_EQUAL(token4.type(), COMMENT);
      CHECK_EQUAL(token4.value(), "Comment number three");
    }

    TEST(ReadResultTest)
    {
      std::string str("* 1-0 0-1 1/2-1/2");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.GetNextToken();
      CHECK_EQUAL(token1.type(), RESULT);
      CHECK_EQUAL(token1.value(), "*");

      PgnToken token2 = tokenizer.GetNextToken();
      CHECK_EQUAL(token2.type(), RESULT);
      CHECK_EQUAL(token2.value(), "1-0");

      PgnToken token3 = tokenizer.GetNextToken();
      CHECK_EQUAL(token3.type(), RESULT);
      CHECK_EQUAL(token3.value(), "0-1");

      PgnToken token4 = tokenizer.GetNextToken();
      CHECK_EQUAL(token4.type(), RESULT);
      CHECK_EQUAL(token4.value(), "1/2-1/2");
    }

    TEST(ReadNumberTest)
    {
      std::string str("1 236 3");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.GetNextToken();
      CHECK_EQUAL(token1.type(), NUMBER);
      CHECK_EQUAL(token1.value(), "1");

      PgnToken token2 = tokenizer.GetNextToken();
      CHECK_EQUAL(token2.type(), NUMBER);
      CHECK_EQUAL(token2.value(), "236");

      PgnToken token3 = tokenizer.GetNextToken();
      CHECK_EQUAL(token3.type(), NUMBER);
      CHECK_EQUAL(token3.value(), "3");

    }

    TEST(ReadSymbolTest)
    {
      std::string str(". ... !?");
      std::istringstream is(str);
      PgnTokenizer tokenizer(&is);
      CHECK(!tokenizer.eof());

      PgnToken token1 = tokenizer.GetNextToken();
      CHECK_EQUAL(token1.type(), SYMBOL);
      CHECK_EQUAL(token1.value(), ".");

      PgnToken token2 = tokenizer.GetNextToken();
      CHECK_EQUAL(token2.type(), SYMBOL);
      CHECK_EQUAL(token2.value(), "...");

      PgnToken token3 = tokenizer.GetNextToken();
      CHECK_EQUAL(token3.type(), SYMBOL);
      CHECK_EQUAL(token3.value(), "!");

      PgnToken token4 = tokenizer.GetNextToken();
      CHECK_EQUAL(token4.type(), SYMBOL);
      CHECK_EQUAL(token4.value(), "?");
    }

    /*TEST(tmp)
    {
      std::ifstream in("pgn/hard.pgn");
      
      PgnTokenizer tokenizer(&in);

      while (!tokenizer.eof())
      {
        PgnToken t = tokenizer.GetNextToken();
        std::cout <<t.value() <<std::endl;
      }

      in.close();
    }*/
  }
}
