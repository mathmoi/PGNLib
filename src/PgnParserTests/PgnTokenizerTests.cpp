#include "../catch/catch.hpp"

#include "../PgnParser/PgnTokenizer.hpp"

TEST_CASE("PgnTokenizer.ReadWordTokens")
{
   std::string str("   Bonjour le\t    \r \n  monde \r\n\t   ");
   std::istringstream is(str);
   m8db::PgnTokenizer tokenizer(&is);
   REQUIRE(!tokenizer.eof());

   m8db::PgnToken token1 = tokenizer.GetNextToken();
   REQUIRE(token1.type() == m8db::WORD);
   REQUIRE(token1.value() == "Bonjour");

   m8db::PgnToken token2 = tokenizer.GetNextToken();
   REQUIRE(token2.type() == m8db::WORD);
   REQUIRE(token2.value() == "le");

   m8db::PgnToken token3 = tokenizer.GetNextToken();
   REQUIRE(token3.type() == m8db::WORD);
   REQUIRE(token3.value() == "monde");

   REQUIRE(!is.good());
   REQUIRE(tokenizer.eof());
}

TEST_CASE("PgnTokenizer.ReadStringTest")
{
   std::string str(" \"Bonjour le monde\" \"Comment \\\\allez \\\"vous\\\"?\"  ");
   std::istringstream is(str);
   m8db::PgnTokenizer tokenizer(&is);
   REQUIRE(!tokenizer.eof());

   m8db::PgnToken token1 = tokenizer.GetNextToken();
   REQUIRE(token1.type() == m8db::STRING);
   REQUIRE(token1.value() == "Bonjour le monde");

   m8db::PgnToken token2 = tokenizer.GetNextToken();
   REQUIRE(token2.type() == m8db::STRING);
   REQUIRE(token2.value() == "Comment \\allez \"vous\"?");

   REQUIRE(!is.good());
   REQUIRE(tokenizer.eof());
}

TEST_CASE("PgnTokenizer.ReadCommentTest")
{
   std::string str(" {Comment number one} \n  alloa ; Comment number two\n {Comment number three}");
   std::istringstream is(str);
   m8db::PgnTokenizer tokenizer(&is);
   REQUIRE(!tokenizer.eof());

   m8db::PgnToken token1 = tokenizer.GetNextToken();
   REQUIRE(token1.type() == m8db::COMMENT);
   REQUIRE(token1.value() == "Comment number one");

   m8db::PgnToken token2 = tokenizer.GetNextToken();
   REQUIRE(token2.type() == m8db::WORD);
   REQUIRE(token2.value() == "alloa");

   m8db::PgnToken token3 = tokenizer.GetNextToken();
   REQUIRE(token3.type() == m8db::COMMENT);
   REQUIRE(token3.value() == " Comment number two");

   m8db::PgnToken token4 = tokenizer.GetNextToken();
   REQUIRE(token4.type() == m8db::COMMENT);
   REQUIRE(token4.value() == "Comment number three");
}

TEST_CASE("PgnTokenizer.ReadResultTest")
{
   std::string str("* 1-0 0-1 1/2-1/2");
   std::istringstream is(str);
   m8db::PgnTokenizer tokenizer(&is);
   REQUIRE(!tokenizer.eof());

   m8db::PgnToken token1 = tokenizer.GetNextToken();
   REQUIRE(token1.type() == m8db::RESULT);
   REQUIRE(token1.value() == "*");

   m8db::PgnToken token2 = tokenizer.GetNextToken();
   REQUIRE(token2.type() == m8db::RESULT);
   REQUIRE(token2.value() == "1-0");

   m8db::PgnToken token3 = tokenizer.GetNextToken();
   REQUIRE(token3.type() == m8db::RESULT);
   REQUIRE(token3.value() == "0-1");

   m8db::PgnToken token4 = tokenizer.GetNextToken();
   REQUIRE(token4.type() == m8db::RESULT);
   REQUIRE(token4.value() == "1/2-1/2");
}

TEST_CASE("PgnTokenizer.ReadNumberTest")
{
   std::string str("1 236 3");
   std::istringstream is(str);
   m8db::PgnTokenizer tokenizer(&is);
   REQUIRE(!tokenizer.eof());

   m8db::PgnToken token1 = tokenizer.GetNextToken();
   REQUIRE(token1.type() == m8db::NUMBER);
   REQUIRE(token1.value() == "1");

   m8db::PgnToken token2 = tokenizer.GetNextToken();
   REQUIRE(token2.type() == m8db::NUMBER);
   REQUIRE(token2.value() == "236");

   m8db::PgnToken token3 = tokenizer.GetNextToken();
   REQUIRE(token3.type() == m8db::NUMBER);
   REQUIRE(token3.value() == "3");

}

TEST_CASE("PgnTokenizer.ReadSymbolTest")
{
   std::string str(". ... !?");
   std::istringstream is(str);
   m8db::PgnTokenizer tokenizer(&is);
   REQUIRE(!tokenizer.eof());

   m8db::PgnToken token1 = tokenizer.GetNextToken();
   REQUIRE(token1.type() == m8db::SYMBOL);
   REQUIRE(token1.value() == ".");

   m8db::PgnToken token2 = tokenizer.GetNextToken();
   REQUIRE(token2.type() == m8db::SYMBOL);
   REQUIRE(token2.value() == "...");

   m8db::PgnToken token3 = tokenizer.GetNextToken();
   REQUIRE(token3.type() == m8db::SYMBOL);
   REQUIRE(token3.value() == "!");

   m8db::PgnToken token4 = tokenizer.GetNextToken();
   REQUIRE(token4.type() == m8db::SYMBOL);
   REQUIRE(token4.value() == "?");
}