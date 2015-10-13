#include "../catch/catch.hpp"

#include "../PgnParser/PgnTags.hpp"

TEST_CASE("SEVEN_TAGS_ROOSTER")
{
   m8db::PgnTags tags;

   REQUIRE(7u == tags.size());

   tags["Event"] = "Tournament";
   REQUIRE("Tournament" == tags["Event"]);

   tags.erase("Event");
   REQUIRE(7u == tags.size());
   REQUIRE("" == tags["Event"]);
   REQUIRE(7u == tags.size());

   tags["Url"] = "http://mathieupage.com";
   REQUIRE(8u == tags.size());

   tags.erase("Url");
   REQUIRE(7u == tags.size());

   tags["aaaa"] = "aaaaaaaa";
   REQUIRE("aaaa" == (--tags.end())->first);
}