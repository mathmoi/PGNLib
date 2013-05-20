#include "PgnTags.hpp"

namespace Pgn
{
  const std::map<std::string, unsigned int> PgnTags::STR = {{"Event", 1}, {"Site", 2}, {"Date", 3}, {"Round", 4}, {"White", 5}, {"Black", 6}, {"Result", 7}};

  bool PgnTags::TagsCompare(const std::string& t1, const std::string& t2)
  {
    // We now get the positions of the tags in the SRT. If they are not in the 
    // SRT we give them the position 8.
    auto it1 = STR.find(t1);
    unsigned int pos1 = it1 != STR.end() ? it1->second : 8;
    auto it2 = STR.find(t2);
    unsigned int pos2 = it2 != STR.end() ? it2->second : 8;

    // We return true if the position of t1 is smaller than the position of t2 
    // or if they are both 8 and t1 is less than t2.
    return pos1 < pos2 || (pos1 == 8 && pos2 == 8 && t1 < t2);
  }

  PgnTags::PgnTags()
    : tags_(TagsCompare)
  {
    // We add the Seven Roster Tags with empty values.
    for (auto pair: STR)
    {
      tags_[pair.first] = "";
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
    for (auto pair: STR)
    {
      tags_[pair.first] = "";
    }
  }
}
