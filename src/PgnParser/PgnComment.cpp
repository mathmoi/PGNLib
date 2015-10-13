/**
* @file PgnComment.cpp
*
* Contains the PgnComment class definitions.
*
* @author Mathieu Pagé (m@mathieupage.com)
*/

#include <string>

#include "PgnComment.hpp"

namespace m8db
{
   class PgnComment::Impl
   {
   private:
      PgnComment* back_ptr_;
   public:
      Impl(PgnComment* back_ptr,
           const std::string comment)
         : back_ptr_(back_ptr),
           comment_(comment)
      {};

      std::string comment_;
   };

   PgnComment::PgnComment(const char* comment)
      : impl_(new PgnComment::Impl(this, std::string(comment)))
   {};

   PgnComment::~PgnComment()
   {
      delete impl_;
   }

   PgnMoveTextItem* PgnComment::Clone() const
   {
      return new PgnComment(impl()->comment_.c_str());
   }

   const char* PgnComment::comment() const
   {
      return impl()->comment_.c_str();
   }

   void PgnComment::set_comment(const char* comment)
   {
      impl()->comment_.assign(comment);
   }
}