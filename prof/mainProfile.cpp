#include <fstream>
#include <iostream>
#include "../src/PgnParser.hpp"

int main(int argc, char* argv[])
{
  std::ifstream in("/home/mathmoi/Desktop/IB1310B.pgn");
  Pgn::PgnParser parser(&in);

  unsigned int count = 0;
  while (!parser.eof())
  {
    Pgn::PgnGame game = parser.ParseSingleGame();
    ++count;

    if (count % 1000 == 0)
    {
      std::cout <<'\r' <<count <<" games parsed";
      std::cout.flush();
    }
  }
  std::cout <<'\r' <<count <<" games parsed" <<std::endl;

  return 0;
}
