#include <fstream>
#include <iostream>

#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/PgnParser.hpp"

namespace PgnParser
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

      std::shared_ptr<PgnMove> move = std::static_pointer_cast<PgnMove>(game[0]);
      CHECK_EQUAL("e4", move->move());

      move = std::static_pointer_cast<PgnMove>(*(game.end() - 1));
      CHECK_EQUAL("Nb5", move->move());

/*
      for (std::shared_ptr<PgnMoveTextItem> item: game)
      {
        if (std::dynamic_pointer_cast<PgnMove>(item))
        {
          std::shared_ptr<PgnMove> move = std::static_pointer_cast<PgnMove>(item);
          std::cout <<move->move() <<std::endl;
        }
      }
*/

      in.close();
    }

    TEST(ParseSuffixAnnotation)
    {
      std::string input = "1. e4!! e5? 2. f4";
      std::istringstream stream(input);
      PgnParser parser(&stream);
      
      PgnGame game = parser.ParseSingleGame();

      CHECK_EQUAL(5u, game.end() - game.begin());

      std::shared_ptr<PgnNag> nag = std::dynamic_pointer_cast<PgnNag>(*(game.begin() + 1));

      CHECK(nag);
      CHECK_EQUAL(static_cast<uint8_t>(NAG::VERY_GOOD_MOVE), nag->nag());

      /*for (std::shared_ptr<PgnMoveTextItem> item: game)
      {
        std::cout <<typeid(item).name() <<std::endl;

        if (std::dynamic_pointer_cast<PgnMove>(item))
        {
          std::shared_ptr<PgnMove> move = std::static_pointer_cast<PgnMove>(item);
          std::cout <<move->move() <<std::endl;
        }
      }*/
    }
  }
}
