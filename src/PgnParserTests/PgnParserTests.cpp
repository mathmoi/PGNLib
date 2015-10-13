#include "../catch/catch.hpp"

#include "../PgnParser/PgnParser.hpp"

#include <fstream>

TEST_CASE("ParseTags")
{
   std::ifstream in("pgn/simple.pgn");
   m8db::PgnParser parser(&in);
   m8db::PgnGame game = parser.ParseSingleGame();

   REQUIRE(11u == game.tags().size());
   REQUIRE("2010.02.21" == game.tags()["Date"]);

   m8db::PgnMove* move = static_cast<m8db::PgnMove*>(game[0]);
   REQUIRE(28u == move->to());

   move = static_cast<m8db::PgnMove*>(*(game.end() - 1));
   REQUIRE(33u == move->to());

   in.close();
}

TEST_CASE("ParseSuffixAnnotation")
{
   std::string input = "1. e4!! e5? 2. f4 *";
   std::istringstream stream(input);
   m8db::PgnParser parser(&stream);

   m8db::PgnGame game = parser.ParseSingleGame();

   REQUIRE(5u == game.end() - game.begin());

   m8db::PgnNag* nag = dynamic_cast<m8db::PgnNag*>(*(game.begin() + 1));

   REQUIRE(nag);
   REQUIRE(static_cast<uint8_t>(m8db::NAG::VERY_GOOD_MOVE) == nag->nag());
}

TEST_CASE("ParseSubVariation")
{
   std::string input = "1. e4 (1. Nc3 e5) e5 2. f4 *";
   std::istringstream stream(input);
   m8db::PgnParser parser(&stream);

   m8db::PgnGame game = parser.ParseSingleGame();

   REQUIRE(4u == game.end() - game.begin());

   m8db::PgnVariation* variation = dynamic_cast<m8db::PgnVariation*>(*(game.begin() + 1));
   REQUIRE(variation);

   m8db::PgnMove* move = dynamic_cast<m8db::PgnMove*>(*variation->begin());
   REQUIRE(move);
   REQUIRE(move->to() == 18);
}

TEST_CASE("ParseComment")
{
   std::string input = "1. e4 {wow} e5 2. f4 ; super\nf5 *";
   std::istringstream stream(input);
   m8db::PgnParser parser(&stream);

   m8db::PgnGame game = parser.ParseSingleGame();

   REQUIRE(6u == game.end() - game.begin());

   m8db::PgnComment* comment = dynamic_cast<m8db::PgnComment*>(*(game.begin() + 1));
   REQUIRE(comment);
   REQUIRE("wow" == std::string(comment->comment()));

   comment = dynamic_cast<m8db::PgnComment*>(*(game.begin() + 4));
   REQUIRE(comment);
   REQUIRE(" super" == std::string(comment->comment()));
}

TEST_CASE("ReadSimplePgn")
{
   std::vector<m8db::PgnGame> games;

   std::ifstream in("pgn/simple.pgn");
   m8db::PgnParser parser(&in);

   while (!parser.eof())
   {
      m8db::PgnGame game = parser.ParseSingleGame();
      games.push_back(game);
   }

   REQUIRE(5u == games.size());
}

TEST_CASE("ReadTestPgn")
{
   std::vector<m8db::PgnGame> games;

   std::ifstream in("pgn/test.pgn");
   m8db::PgnParser parser(&in);

   while (!parser.eof())
   {
      m8db::PgnGame game = parser.ParseSingleGame();
      games.push_back(game);
   }

   REQUIRE(7u == games.size());
}

TEST_CASE("ReadHardPgn")
{
   std::vector<m8db::PgnGame> games;

   std::ifstream in("pgn/hard.pgn");
   m8db::PgnParser parser(&in);

   while (!parser.eof())
   {
      m8db::PgnGame game = parser.ParseSingleGame();
      games.push_back(game);
   }

   REQUIRE(2u == games.size());
}