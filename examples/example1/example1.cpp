#include <iostream>
#include <fstream>
#include <PgnParser.hpp>

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cout <<"Usage: " <<argv[0] <<" {Path to pgn file}" <<std::endl;
    return 1;
  }

  // We try to open the pgn file
  std::ifstream in(argv[1], std::ios_base::in);
  if (in.fail())
  {
    std::cout <<"Unable to open the file \"" <<argv[1] <<"\"." <<std::endl;
    return 2;
  }

  try
  {
    Pgn::PgnParser parser(&in);

    while(!parser.eof())
    {
      Pgn::PgnGame game = parser.ParseSingleGame();

      // We display both players name.
      std::cout <<game.tags()["White"] << " - " <<game.tags()["Black"] <<std::endl;

      // We display all move in the format "from - to"
      for (auto item : game)
      {
        Pgn::PgnMove* move = dynamic_cast<Pgn::PgnMove*>(item);
        if (move)
        {
          std::cout <<static_cast<char>('a' + (move->from() % 8)) <<(move->from() / 8) + 1 <<" - " <<static_cast<char>('a' + (move->to() % 8)) <<(move->to() / 8) + 1 <<std::endl;
        }
      }

      std::cout <<std::endl;
    }
  }
  catch (std::runtime_error e)
  {
    std::cout <<"Unable to parse game in \"" <<argv[1] <<"\"." <<std::endl
              <<"Reason: " <<e.what() <<std::endl;
  }

  in.close();
  return 0;
}
