#ifndef INCLUDE_PGN_TAGS_HPP_
#define INCLUDE_PGN_TAGS_HPP_

#include <set>
#include <map>
#include <string>

namespace PgnLib
{
  /**
   * Represent the tags section of a PgnGame.
   *
   * The PgnTags object has an interface reminescent of std::map. It contains
   * name/value pair representing the tag pair found in a PgnGame. Since the
   * PGN specifications stipulate that the tags from the Seven Tag Roster (STR)
   * need to always be present they are automatically added to the map when 
   * it's created and it's impossible to remove them. Trying to erase them will
   * just reset their value to an empty string.
   */
  class PgnTags
  {
  private:
    typedef std::map<std::string, std::string> tags_map;

  public:
    /**
     * Type of an iterator used to iterate over tags contained in PgnTags
     */
    typedef tags_map::iterator iterator;

    /**
     * Type of a const iterator used to iterate over tags contained in PgnTags
     */
    typedef tags_map::const_iterator const_iterator;

  private:
    static const std::set<std::string> STR;

    tags_map tags_;

  public:
    /**
     * Constructor
     */
    PgnTags();

    /**
     * Returns an iterator pointing on the first tag key/value pair
     *
     * Note that the items the iterator is pointing to is of type 
     * std::pair<std::string, std::string> where the first value is the tag's 
     * name and the second value is the tag's value.
     *
     * @return  An iterator pointing on the first tag name/value pair
     */
    inline iterator begin() { return tags_.begin(); };

    /**
     * Returns an iterator pointing to the past-the-end tag position
     *
     * Note that the items the iterator is pointing to is of type 
     * std::pair<std::string, std::string> where the first value is the tag's 
     * name and the second value is the tag's value.
     *
     * @return  An iterator pointing to the past-the-end tag position
     */
    inline iterator end() { return tags_.end(); };

    /**
     * Returns an iterator pointing on the first tag key/value pair
     *
     * Note that the items the iterator is pointing to is of type 
     * std::pair<std::string, std::string> where the first value is the tag's 
     * name and the second value is the tag's value.
     *
     * This is the version called when the tag object is const-qualified.
     *
     * @return  An iterator pointing on the first tag name/value pair
     */
    inline const_iterator begin() const { return tags_.begin(); };

    /**
     * Returns an iterator pointing to the past-the-end tag position
     *
     * Note that the items the iterator is pointing to is of type 
     * std::pair<std::string, std::string> where the first value is the tag's 
     * name and the second value is the tag's value.
     *
     * This is the version called when the tag object is const-qualified.
     *
     * @return  An iterator pointing to the past-the-end tag position
     */
    inline const_iterator end() const { return tags_.end(); };

    /**
     * Get the number of tags contained in the object.
     *
     * @return  the number of tags contained in the object
     */
    inline unsigned int size() const { return tags_.size(); };

    /**
     * Overload of the operator[] used to access a specific tag's value.
     *
     * @warning If no tag with the name resquested is found one is added and 
     *          a reference to it's value is returned.
     *
     * That means that you can use the [] operator to add a tag like this :
     *
     * @code
     *  tags["NewTagName"] = "New tag value";
     * @endcode
     *
     * However if you don't wish to add a tag if it's not present you need to 
     * first check if the tag when it's not present using the 
     * PgnTags::count(const std::string&) method.
     *
     * @param   key   name of the tag we want to get.
     *
     * @return  A reference to the value of the tag requested
     */
    inline std::string& operator[](const std::string& key) { return tags_[key]; };

    /**
     * Remove a tag from the list
     *
     * If the tag is one of the Seven Tags Roster it is not removed. Instead 
     * it's value is set to an empty string.
     *
     * @param   key   Name of the tag to remove
     */
    void erase(const std::string& key);

    /**
     * Returns the number of tags with the name key contained in the object.
     *
     * Since tags can't be duplicated, the function will always return 0 or 1.
     *
     * @param   key   Name of the tag we want to count
     *
     * @return  1 if the tag is found, otherwise 0.
     */
    inline unsigned int count(const std::string& key) const { return tags_.count(key); };

    /**
     * Remove all tags.
     *
     * The Seven Tags Roster tags are not removed, instead their value is 
     * initialized to the empty string.
     */
    void clear();    
  };
}

#endif // INCLUDE_PGN_TAGS_HPP_
