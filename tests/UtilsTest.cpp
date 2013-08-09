#include <string>
#include <vector>

#include <UnitTest++.h>
#include <Utils.hpp>

namespace PgnLib
{
  SUITE(UtilsTests)
  {
    TEST(Split)
    {
      std::string s = "Bonjour le monde!";
      char delim = ' ';

      std::vector<std::string> tokens = split(s, delim);
      CHECK(tokens.size() == 3);
      CHECK(tokens[1] == "le");
    }
  }
}
