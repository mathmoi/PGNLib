#include <iostream> // TODO : enlever
#include <string>

#include "../libs/UnitTest++/include/UnitTest++.h"

#include "../src/PgnTags.hpp"

namespace PgnParser
{
  SUITE(PgnTagsTests)
  {
    TEST(SevenTagsRoster)
    {
      PgnTags tags;

      CHECK_EQUAL(7u, tags.size());

      tags["Event"] = "Tournament";
      CHECK_EQUAL("Tournament", tags["Event"]);

      tags.erase("Event");
      CHECK_EQUAL(7u, tags.size());
      CHECK_EQUAL("", tags["Event"]);
      CHECK_EQUAL(7u, tags.size());

      tags["Url"] = "http://mathieupage.com";
      CHECK_EQUAL(8u, tags.size());

      tags.erase("Url");
      CHECK_EQUAL(7u, tags.size());

      tags["aaaa"] = "aaaaaaaa";
      CHECK_EQUAL("aaaa", (--tags.end())->first);
    }


  }
}
