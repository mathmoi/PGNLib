/**
* @file   DeepConstPtr.hpp
* @author Mathieu Pagé (m@mathieupage.com)
* @Date   August, 2015
*
* Contains the definition of the DeepConstPtr class that allows the creation of
* pointers to implementation that preserve constness.
*/

namespace m8db
{
   template<typename PointerType>
   class DeepConstPtr
   {
      PointerType* ptr_;

   public:
      explicit DeepConstPtr(PointerType* ptr) : ptr_(ptr) {};

      const PointerType & operator*() const { return *p; };
      PointerType & operator*() { return *p; };

      const PointerType * operator->() const { return p; };
      PointerType * operator->() { return p; };
   };
}