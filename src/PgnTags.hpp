#ifndef INCLUDE_PGN_TAGS_HPP_
#define INCLUDE_PGN_TAGS_HPP_

#include <map>
#include <string>

namespace Pgn
{
  class PgnTags
  {
  public:
    typedef std::map<std::string, std::string, bool (*)(const std::string&, const std::string&)> tags_map;
    typedef tags_map::iterator iterator;
    typedef tags_map::const_iterator const_iterator;

  private:
    static const std::map<std::string, unsigned int> STR;
    static bool TagsCompare(const std::string& t1, const std::string& t2);

    tags_map tags_;

  public:
    PgnTags();

    inline iterator begin() { return tags_.begin(); };
    inline iterator end() { return tags_.end(); };
    inline const_iterator begin() const { return tags_.begin(); };
    inline const_iterator end() const { return tags_.end(); };

    inline unsigned int size() const { return tags_.size(); };
    inline std::string& operator[](const std::string& key) { return tags_[key]; };
    void erase(const std::string& key);
    inline unsigned int count(const std::string& key) const { return tags_.count(key); };
    void clear();    
  };
}

#endif // INCLUDE_PGN_TAGS_HPP_
