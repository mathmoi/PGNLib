/**
* @file PgnComment.hpp
*
* Contains the PgnComment class.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/
#ifndef INCLUDE_PGN_COMMENT_HPP_
#define INCLUDE_PGN_COMMENT_HPP_

#include <string>
#include <memory>

#include "DllPort.hpp"

#include "PgnMoveTextItem.hpp"

namespace m8db
{
   /**
    * Represent a comment in a PGN game's movetext.
    */
   class DLLPORT PgnComment : public PgnMoveTextItem
   {
   private:
      class Impl;
      PgnComment::Impl* impl_;

      /**
       * Returns a const pointer to the implementation.
       */
      inline const Impl * impl() const { return impl_; };

      /**
       * Returns a non const pointer to the implementation.
       */
      inline Impl * impl() { return impl_; };

   public:
      /**
       * Construct a new comment.
       *
       * @param   comment   Text of the new comment.
       */
      PgnComment(const char* comment);

      /**
       * Destructor
       */
      ~PgnComment();

      /**
       * Creates a copy of the PgnComment
       *
       * This function create a dynamically allocated copy of the item. The code
       * which calls the function must assume ownership of the allocated memory
       * and is responsible for releasing it eventually.
       *
       * @return a pointer to a dynamically allocated copy of the object.
       */
      PgnMoveTextItem* Clone() const;

      /**
       * Get the comment's text.
       *
       * @return    The comment's text
       */
      const char* comment() const;

      /**
       * Set the comment's text
       *
       * @param   comment   New comment's text.
       */
      void set_comment(const char* comment);
   };
}

#endif // INCLUDE_PGN_COMMENT_HPP_
