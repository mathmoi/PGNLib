#include "PgnTags.hpp"

namespace m8db
{
  std::set<std::string> CreateSTR()
  {
    static const std::string s[] = {"Event", "Site", "Date", "Round", "White", "Black", "Result"};
    std::set<std::string> str(s, s + 7);
    return str;
  }
  const std::set<std::string> PgnTags::STR = CreateSTR();

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
