#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <stdexcept>
#include <cstddef>

namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Vector abstract data type
/// @ingroup MySTL
/// @tparam T Data type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior, e.g.,
/// front().
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class vector {
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef T* iterator;             ///< Random access iterator
    typedef const T* const_iterator; ///< Const random access iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{
    /// @brief Default constructor
    /// @param n Size
    /// @param val Initial value
    vector(size_t n = 0, const T& val = T()) : cap(std::max(size_t(10), 2*n)), sz(n) {
      /// @todo Implement default construction
      t = new T[cap];
	 for(size_t i=0;i<sz;i++) //sets all indices in T up to sz equal to val
		t[i]=val;
    }
    /// @brief Copy constructor
    /// @param v
    vector(const vector& v) : cap(v.cap), sz(v.sz) {
      /// @todo Implement copy construction
      t = new T[cap];
	  for(size_t i=0;i<sz;i++) //copies all elements from v to t
		t[i]=v[i];
    }
    /// @brief Destructor
    ~vector() {
      /// @todo Implement destruction
		delete[] t; //delete
    }

    /// @brief Copy assignment
    /// @param v
    /// @return Reference to self
 vector& operator=(const vector& v) {
      /// @todo Implement copy assignment
	 cap=v.cap;
	 sz=v.sz;
	  t=new T[cap];
	  for(size_t i=0;i<sz;i++) //same as the other copy constructor
		t[i]=v[i];
      return *this;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return t;}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return t;}
    /// @return Iterator to end
    iterator end() {return &t[sz];}
    /// @return Iterator to end
    const_iterator cend() const {return &t[sz];}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of vector
    size_t size() const {return sz;}
    /// @return Capacity of underlying array
    size_t capacity() const {return cap;}
    /// @return Does the vector contain anything?
    bool empty() const {return sz == 0;}

    /// @brief  the array
    /// @param n ResizeSize
    /// @param val Value if size is greater of default elements
    ///
    /// If the new size is less than the current progressively remove elements
    /// in the array. Otherwise progressively insert values at the end equal to
    /// \c val.
    void resize(size_t n, const T& val = T()) {
      /// @todo Implement resize (hint: use push_back and pop_back)
	 if(n>cap) //resizes the array with the reserve function,popback, or push_back depending on the argument
		 reserve(n*2);
	 if(n<sz){
		  while(n!=sz)
		  pop_back();
	 }
	 if(n>sz){
		 while(n!=sz)
		 push_back(val);
	 }
	 
	 sz=n;
	 
    }
    /// @brief Request a change in the capacity
    /// @param c Capacity
    ///
    /// If the capacity is equal or less than the current capacity, nothing
    /// happens. If the capacity is greater, then the vector is reallocated and
    /// and contents copied.
    void reserve(size_t c) {
      /// @todo Implement reserve (hint: this function can be reused elsewhere)
	  if(c<cap)
		  return;
								//creates a temporary array to copy into and makes it the new array
	  T * temp = new T[c];
	  for (size_t i = 0; i < sz; i++)
        temp[i] = t[i];

		cap=c;
		delete[] t;
		t = temp;
 
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @brief Element access without range check
    /// @param i Index
    /// @return Element at \c i
    T& operator[](size_t i) {return t[i];}
    /// @brief Element access without range check
    /// @param i Index
    /// @return Element at \c i
    const T& operator[](size_t i) const {return t[i];}
    /// @brief Element access with range check
    /// @param i Index
    /// @return Element at \c i
    T& at(size_t i) {
      if(i < 0 || i >= sz)
        throw std::out_of_range("Invalid Array Access");
      return t[i];
    }
    /// @brief Element access with range check
    /// @param i Index
    /// @return Element at \c i
    const T& at(size_t i) const {
      if(i < 0 || i >= sz)
        throw std::out_of_range("Invalid Array Access");
      return t[i];
    }
    /// @return Element at front of vector
    T& front() {return t[0];}
    /// @return Element at front of vector
    const T& front() const {return t[0];}
    /// @return Element at back of vector
    T& back() {return t[sz-1];}
    /// @return Element at back of vector
    const T& back() const {return t[sz-1];}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Add element to end of vector, when capacity is reached perform
    ///        doubling strategy.
    /// @param val Element
    void push_back(const T& val) {
      /// @todo Implement push back
	  if(sz==cap)  //sets sz'th element to val and if it runs out of room, it reserves more.
		  reserve(cap*2);
	  if(sz<cap){
		  t[sz]=val;
		  sz++;
	  }
    }
    /// @brief Add element to end of vector, when capacity is reached perform
    ///        incremental strategy.
    /// @param val Element
    void push_back_incremental(const T& val) {
      /// @todo Implement push back with incremental capacity increase
	  if(sz==cap) //same thing as push_back but it reserves cap+10
		reserve(cap+10);
	  if(sz<cap){
		  t[sz]=val;
		  sz++;
	  }
    }
    /// @brief Remove the last element of the vector
    void pop_back() {
	  t[sz-1]=T(); //delete's the sz-1'th element
	  sz--;
      /// @todo Implement pop back
    }
    /// @brief Insert element before specified position
    /// @param i Position
    /// @param val Value
    /// @return Position of new value
    iterator insert(iterator i, const T& val) {
      /// @bonus Implement insert for bonus
      return iterator();
    }
    /// @brief Remove element at specified position
    /// @param i Position
    /// @return Position of new location of element which was after eliminated
    ///         one
    iterator erase(iterator i) {
      /// @bonus Implement erase for bonus
      return iterator();
    }
    /// @brief Removes all elements without resizing the capacity of the array
    void clear() {
      /// @todo Implement clear
	 for(size_t i=0;i<sz;i++)
		 t[i]=T();
	 sz=0;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:
    T* t;       ///< Dynamically allocated array
    size_t cap; ///< Capacity
    size_t sz;  ///< Size
};

}

#endif
