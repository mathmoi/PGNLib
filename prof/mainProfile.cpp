#include <fstream>
#include <iostream>
#include "../include/PgnParser.hpp"

int main(int , char**)
{
  std::ifstream in("/home/mathmoi/Desktop/IB1310B.pgn");
  PgnLib::PgnParser parser(&in);

  unsigned int count = 0;
  while (!parser.eof())
  {
    PgnLib::PgnGame game = parser.ParseSingleGame();
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
