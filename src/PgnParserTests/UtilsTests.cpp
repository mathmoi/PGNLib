#include "../catch/catch.hpp"

#include "../PgnParser/Utils.hpp"

TEST_CASE("Split")
{
   std::string s = "Bonjour le monde!";
   char delim = ' ';

   std::vector<std::string> tokens = m8db::split(s, delim);
   REQUIRE(tokens.size() == 3);
   REQUIRE(tokens[1] == "le");
}