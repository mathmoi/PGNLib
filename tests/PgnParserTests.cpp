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
      PgnGame game = parser.parse_single_game();

      CHECK_EQUAL(11u, game.tags().size());
      CHECK_EQUAL("2010.02.21", game.tags()["Date"]);

      /*std::shared_ptr<PgnMove> move = std::static_pointer_cast<PgnMove>(game.get_move_text().get_items()[0]);
      CHECK_EQUAL("e4", move->get_move());

      unsigned int size = game.get_move_text().get_items().size();
      move = std::static_pointer_cast<PgnMove>(game.get_move_text().get_items()[size - 1]);
      CHECK_EQUAL("Nb5", move->get_move());*/

      /*for (std::shared_ptr<PgnMoveTextItem> item: game.get_move_text().get_items())
      {
        if (item->get_type() == ITEM_MOVE)
        {
          std::shared_ptr<PgnMove> move = std::static_pointer_cast<PgnMove>(item);
          std::cout <<move->get_move() <<std::endl;
        }
      }*/

      in.close();
    }
  }
}
