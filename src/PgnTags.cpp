#include "../include/PgnTags.hpp"

namespace Pgn
{
  const std::set<std::string> PgnTags::STR = {"Event", "Site", "Date", "Round", "White", "Black", "Result"};

  PgnTags::PgnTags()
    : tags_()
  {
    // We add the Seven Roster Tags with empty values.
    for (auto tag : STR)
    {
      tags_[tag] = "";
    }
  }

  void PgnTags::erase(const std::string& key)
  {
    // If the key is one of the Seven Roster Tag we just reset it's value. 
    // Otherwise, we erase it from the map;
    auto it = STR.find(key);
    if (it != STR.end())
    {
      tags_[key] = "";
    }
    else
    {
      tags_.erase(key);
    }
  }

  void PgnTags::clear()
  {
    tags_.clear();

    // Since the Seven Roster Tags must always be in the map we need to 
    // reintroduce them with empty values.
    for (auto tag : STR)
    {
      tags_[tag] = "";
    }
  }
}
