#ifndef INCLUDE_PGN_VARIATION_HPP_
#define INCLUDE_PGN_VARIATION_HPP_

#include <vector>

#include "PgnParserException.hpp"
#include "PgnMoveTextItem.hpp"

namespace PgnLib
{
  class InvalidItemException : public PgnParserException
  {
  public:
    InvalidItemException()
      : PgnParserException("An invalid item was added to a PgnVariation.") {};
  };


  class PgnVariation : public PgnMoveTextItem
  {
  public:
    typedef PgnMoveTextItem* ItemPointer;
    typedef const PgnMoveTextItem* ConstItemPointer;
    typedef std::vector<ItemPointer> ItemsVector;

    typedef ItemsVector::iterator iterator;
    typedef ItemsVector::const_iterator const_iterator;

  private:
    unsigned int first_move_number_;
    bool first_move_white_;
    ItemsVector items_;

  public:
  	inline PgnVariation()
	    : first_move_number_(0),
		    first_move_white_(true) {};

    PgnVariation(const PgnVariation& other);
    PgnVariation(PgnVariation&& other) throw();
    PgnVariation& operator=(PgnVariation other);
    PgnVariation& operator=(PgnVariation&& other);
    ~PgnVariation() throw();


    inline PgnMoveTextItem* Clone() const { return new PgnVariation(*this); };
    void Swap(PgnVariation& other);

    inline void set_first_move_number(unsigned int first_move_number) { first_move_number_ = first_move_number; };
    inline unsigned int first_move_number() const { return first_move_number_; };

    inline void set_first_move_white(bool first_move_white) { first_move_white_ = first_move_white; };
    inline bool first_move_white() const { return first_move_white_; };

    inline ItemPointer operator[](unsigned int n) { return items_[n]; };
    inline ConstItemPointer operator[](unsigned int n) const { return const_cast<const PgnMoveTextItem*>(items_[n]); };

    inline iterator begin() { return items_.begin(); };
    inline const_iterator begin() const { return items_.begin(); };
    inline iterator end() { return items_.end(); };
    inline const_iterator end() const { return items_.end(); };

    void push_back(const ItemPointer& item);

    // This function insert a new element, val, just before the position 
    // pointer by the iterator, it.
    inline void insert(iterator it, const ItemPointer& val) { items_.insert(it, val); };

    // Erase the element pointed by the iterator, it.
    inline void erase(iterator it) { items_.erase(it); };
  };
}

#endif // INCLUDE_PGN_VARIATION_HPP_
