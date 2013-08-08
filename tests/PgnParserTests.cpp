#include <fstream>

#include <UnitTest++.h>
#include <PgnParser.hpp>

namespace Pgn
{
  SUITE(PgnParserTests)
  {
    TEST(ParseTags)
    {
      std::ifstream in("pgn/simple.pgn");
      PgnParser parser(&in);
      PgnGame game = parser.ParseSingleGame();

      CHECK_EQUAL(11u, game.tags().size());
      CHECK_EQUAL("2010.02.21", game.tags()["Date"]);

      PgnMove* move = static_cast<PgnMove*>(game[0]);
      CHECK_EQUAL(28u, move->to());

      move = static_cast<PgnMove*>(*(game.end() - 1));
      CHECK_EQUAL(33u, move->to());

      in.close();
    }

    TEST(ParseSuffixAnnotation)
    {
      std::string input = "1. e4!! e5? 2. f4 *";
      std::istringstream stream(input);
      PgnParser parser(&stream);
      
      PgnGame game = parser.ParseSingleGame();

      CHECK_EQUAL(5u, game.end() - game.begin());

      PgnNag* nag = dynamic_cast<PgnNag*>(*(game.begin() + 1));

      CHECK(nag);
      CHECK_EQUAL(static_cast<uint8_t>(NAG::VERY_GOOD_MOVE), nag->nag());
    }

    TEST(ParseSubVariation)
    {
      std::string input = "1. e4 (1. Nc3 e5) e5 2. f4 *";
      std::istringstream stream(input);
      PgnParser parser(&stream);
      
      PgnGame game = parser.ParseSingleGame();

      CHECK_EQUAL(4u, game.end() - game.begin());

      PgnVariation* variation = dynamic_cast<PgnVariation*>(*(game.begin() + 1));
      CHECK(variation);

      PgnMove* move = dynamic_cast<PgnMove*>(*variation->begin());
      CHECK(move);
      CHECK(move->to() == 18);
    }

    TEST(ParseComment)
    {
      std::string input = "1. e4 {wow} e5 2. f4 ; super\nf5 *";
      std::istringstream stream(input);
      PgnParser parser(&stream);
      
      PgnGame game = parser.ParseSingleGame();

      CHECK_EQUAL(6u, game.end() - game.begin());

      PgnComment* comment = dynamic_cast<PgnComment*>(*(game.begin() + 1));
      CHECK(comment);
      CHECK_EQUAL("wow", comment->comment());

      comment = dynamic_cast<PgnComment*>(*(game.begin() + 4));
      CHECK(comment);
      CHECK_EQUAL(" super", comment->comment());
    }

    TEST(ReadSimplePgn)
    {
      std::vector<PgnGame> games;

      std::ifstream in("pgn/simple.pgn");
      PgnParser parser(&in);

      while (!parser.eof())
      {
        PgnGame game = parser.ParseSingleGame();
        games.push_back(game);
      }

      CHECK_EQUAL(4u, games.size());
    }

    TEST(ReadTestPgn)
    {
      std::vector<PgnGame> games;

      std::ifstream in("pgn/test.pgn");
      PgnParser parser(&in);

      while (!parser.eof())
      {
        PgnGame game = parser.ParseSingleGame();
        games.push_back(game);
      }

      CHECK_EQUAL(7u, games.size());
    }

    TEST(ReadHardPgn)
    {
      std::vector<PgnGame> games;

      std::ifstream in("pgn/hard.pgn");
      PgnParser parser(&in);

      while (!parser.eof())
      {
        PgnGame game = parser.ParseSingleGame();
        games.push_back(game);
      }

      CHECK_EQUAL(2u, games.size());
    }
  }
}
