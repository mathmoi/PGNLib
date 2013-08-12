#ifndef INCLUDE_PGN_VARIATION_HPP_
#define INCLUDE_PGN_VARIATION_HPP_

#include <vector>

#include "PgnParserException.hpp"
#include "PgnMoveTextItem.hpp"

namespace PgnLib
{
  /**
   * Exception thrown when an invalid item is added to a PgnVariation.
   *
   * PgnGames objects are PgnVariations, but should never be added to another
   * variation. If an attempt to do so is made an InvalidItemException is 
   * thrown.
   */
  class InvalidItemException : public PgnParserException
  {
  public:
    InvalidItemException()
      : PgnParserException("An invalid item was added to a PgnVariation.") {};
  };

  /**
   * Represent a sequence of PgnMoveTextItems.
   *
   * Since a PgnGame is a sequence of move, comments and other items, a PgnGame
   * is a PgnVariation. PgnVariation can also be added as an item to another 
   * PgnVariation.
   */
  class PgnVariation : public PgnMoveTextItem
  {
  public:
    /**
     * Type of a pointer to an PgnMoveTextItem
     */
    typedef PgnMoveTextItem* ItemPointer;

    /**
     * Type if a const pointer to a PgnMoveTextItem
     */
    typedef const PgnMoveTextItem* ConstItemPointer;
    
    /// @cond
    typedef std::vector<ItemPointer> ItemsVector;
    /// @endcond
    
    /**
     * Type of iterator returned by begin() and end()
     */
    typedef ItemsVector::iterator iterator;

    /**
     * Type of const iterator returned by begin() and end()
     */
    typedef ItemsVector::const_iterator const_iterator;

  private:
    unsigned int first_move_number_;
    bool first_move_white_;
    ItemsVector items_;

  public:
    /**
     * Default constructor
     *
     * Construct a new, empty variation.
     */
  	inline PgnVariation()
	    : first_move_number_(1),
		    first_move_white_(true) {};

    /**
     * Copy constructor
     */
    PgnVariation(const PgnVariation& other);

    /**
     * Move constructor
     */
    PgnVariation(PgnVariation&& other) throw();

    /**
     * Copy assignment operator
     */
    PgnVariation& operator=(PgnVariation other);

    /**
     * Move assignement operator
     */
    PgnVariation& operator=(PgnVariation&& other);

    /**
     * Destructor
     */
    ~PgnVariation() throw();

    /**
     * Creates a copy of the PgnVariation.
     *
     * This function create a dynamically allocated copy of the variation. The
     * code which calls the function must assume ownership of the allocated 
     * memory and is responsible for releasing it eventually.
     *
     * @return  A pointer to a dynamically allocated copy of the object.
     */
    inline PgnMoveTextItem* Clone() const { return new PgnVariation(*this); };

    /**
     * Swap this object's values with the one passed in parameter.
     *
     * This function is useful to implement the move semantics and the copy
     * assignment operator.
     *
     * @param   other   The values of this object will be swapped with the 
     *                  values of the object on which the method is called.
     */
    void Swap(PgnVariation& other);

    /**
     * Set the number of the first move
     *
     * @param   first_move_number   New value of the first move number.
     */
    inline void set_first_move_number(unsigned int first_move_number) { first_move_number_ = first_move_number; };

    /**
     * Get the first move number.
     *
     * @return  First move number
     */
    inline unsigned int first_move_number() const { return first_move_number_; };

    /**
     * Set first move white
     *
     * If the first move in the variation is from the white player this should 
     * be set to true. Otherwise it should be false.
     *
     * @param   first_move_white  New value of first_move_white
     */
    inline void set_first_move_white(bool first_move_white) { first_move_white_ = first_move_white; };

    /**
     * Get first move white
     *
     * @return  True if the first move of the variation is from the white 
     *          player, false otherwise.
     */
    inline bool first_move_white() const { return first_move_white_; };

    /**
     * Returns a pointer to the element at position `n` in the variation.
     *
     * @param   n   Position of the element we want to retrieve.
     *
     * @return  Pointer to the element at position `n`
     */
    inline ItemPointer operator[](unsigned int n) { return items_[n]; };

    /**
     * Returns a const pointer to the element at position `n` in the variation.
     *
     * @param   n   Position of the element we want to retrieve.
     *
     * @return  Pointer to the element at position `n`
     */
    inline ConstItemPointer operator[](unsigned int n) const { return const_cast<const PgnMoveTextItem*>(items_[n]); };

    /**
     * Return an forward iterator positioned at the begining of the variation.
     *
     * @return  An iterator positioned at the first element in the variation
     */
    inline iterator begin() { return items_.begin(); };

    /**
     * Return an const forward iterator positioned at the begining of the 
     * variation.
     *
     * @return  A const iterator positioned at the first element in the 
     *          variation
     */
    inline const_iterator begin() const { return items_.begin(); };

    /**
     * Returns an iterator refering to the element past the end of the 
     * variation.
     *
     * @return  An iterator position after the last item of the variation.
     */
    inline iterator end() { return items_.end(); };

    /**
     * Returns a const iterator refering to the element past the end of the
     * variation.
     *
     * @return  A const iterator position after the last item of the variation.
     */
    inline const_iterator end() const { return items_.end(); };

    /**
     * Add the item `item` at the end of the variation.
     *
     * The variation takes ownership of the item passed in parameter. When the 
     * variation is destroyed, it will delete the item. It is important to add
     * the item to only one variation. Also, if the calling function keeps a
     * copy of the pointer, it is important that it did not use it after the
     * game has been destroyed.
     *
     * @param   item    Pointer to a dynamically allocated item.
     */
    void push_back(const ItemPointer& item);

    /**
     * This function insert a new element, val, just before the position 
     * pointed by the iterator, it.
     *
     * val needs to point to dynamically allocated memory. The variation takes 
     * ownership of the item passed in parameter. When the variation is 
     * destroyed, it will delete the item. It is important to add the item to 
     * only one variation. Also, if the calling function keeps a copy of the 
     * pointer, it is important that it did not use it after the game has been 
     * destroyed.
     *
     * @param   it    Iterator pointing to the position before which the new 
     *                element should be inserted.
     *
     * @param   val   Pointer to an item in dynamically allocated memory.
     */
    inline void insert(iterator it, const ItemPointer& val) { items_.insert(it, val); };

    /**
     * Erase the element pointed by it.
     *
     * The element will be destroyed. If the client code has a copy of the 
     * pointer, it is important it does not try to use it.
     *
     * @param   it    Itarator pointing to the element that should be erased.
     */
    inline void erase(iterator it) 
    {
      delete *it;
      items_.erase(it);
    };
  };
}

#endif // INCLUDE_PGN_VARIATION_HPP_
