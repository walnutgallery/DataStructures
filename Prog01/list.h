#ifndef _LIST_H_
#define _LIST_H_

#include <iterator>
#include <iostream>

namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Doubly-linked list
/// @ingroup MySTL
/// @tparam T Data type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior, e.g.,
/// front().
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class list {

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Internal structure for linked list
  //////////////////////////////////////////////////////////////////////////////
  struct node {
    T t;        ///< Value
    node* prev; ///< Previous node
    node* next; ///< Next node

    /// @brief Default Constructor
    /// @param val Value
    /// @param p Previous node
    /// @param n Next node
    node(const T& val = T(), node* p = NULL, node* n = NULL) : t(val), prev(p), next(n) {}
  };

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Bidirectional iterator
  //////////////////////////////////////////////////////////////////////////////
  template<typename U>
  class list_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
    public:
      //////////////////////////////////////////////////////////////////////////
      /// @name Constructors
      /// @{

      /// @brief Construction
      /// @param v Pointer to element of vector
      list_iterator(node* v = NULL) : n(v) {}
      /// @brief Copy construction
      /// @param i Iterator
      list_iterator(const list_iterator& i) : n(i.n) {}
      /// @brief Destruction
      ~list_iterator() {}

      /// @brief Copy assignment
      /// @param i Iterator
      list_iterator& operator=(const list_iterator& i) {n = i.n;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Comparison
      /// @{

      /// @brief Equality comparison
      /// @param i Iterator
      bool operator==(const list_iterator& i) const {return n == i.n;}
      /// @brief Inequality comparison
      /// @param i Iterator
      bool operator!=(const list_iterator& i) const {return n != i.n;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Dereference
      /// @{

      /// @brief Dereference operator
      U& operator*() const {return n->t;}
      /// @brief Dereference operator
      U* operator->() const {return &n->t;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Advancement
      /// @{

      /// @brief Pre-increment
      list_iterator& operator++() {n = n->next; return *this;}
      /// @brief Post-increment
      list_iterator operator++(int) {list_iterator tmp(*this); ++(*this); return tmp;}
      /// @brief Pre-decrement
      list_iterator& operator--() {n = n->prev; return *this;}
      /// @brief Post-decrement
      list_iterator operator--(int) {list_iterator tmp(*this); --(*this); return tmp;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      friend class list;

    private:
      node* n; ///< List node
  };

  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef list_iterator<T>
      iterator;               ///< Random access iterator
    typedef list_iterator<const T>
      const_iterator;         ///< Const random access iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Default constructor
    /// @param n Initial size
    /// @param val Initial value
    list(size_t n = 0, const T& val = T()) : head(NULL), tail(NULL), sz(n) {
		/// @todo Implement default construction
 		if(n==0){ //different cases for n<2
			head=new node(T(),NULL,tail);
			tail=new node(T(),head,NULL);
		}
		if(n==1){
			head=new node(val,NULL,tail);
			tail=new node(T(),head,NULL);
		}
		if(n==2){
			head=new node(val,NULL,tail);
			tail=new node(val,head,NULL);
		}
			
		if(n>2){ //creates a head and a new node that has a previous point to head
			head = new node(val,NULL,NULL);
			node* previous_node = new node(val,head,NULL);
			head->next=previous_node;
			
				for(size_t i = 0; i <n-2; i++){ //keeps making new nodes that has a previous that points to the prev and sets the previous's next equal to the new node.
					node* tmp = new node(val, previous_node, NULL);
					previous_node->next=tmp;
					previous_node = tmp;
					}	
						tail = new node(val,previous_node,NULL);
				previous_node->next=tail; //initalizes the tail.
			
		} 
		
		
	}
    /// @brief Copy constructor
    /// @param v
    list(const list& v) {
      /// @todo Implement copy construction
		  clear();	//clears and then pushes back all the elements into the current list
		  size_t runTotal=v.size();
		  const_iterator it=v.cbegin();
		  for(size_t i=0;i<runTotal;i++)	
			  push_back(*it++);
    }
    /// @brief Destructor
    ~list() {
      /// @todo Implement destruction
	 while(sz!=0)
		 pop_back();
    }
    /// @brief Copy assignment
    /// @param v
    /// @return Reference to self
    list& operator=(const list& v) {
      /// @todo Copy assignment
		  clear();	//clears and then pushes back all the elements into the list
		  size_t runTotal=v.size();
		  const_iterator it=v.cbegin();
		  for(size_t i=0;i<runTotal;i++)	
			  push_back(*it++);
		  return *this;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return iterator(head);}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return const_iterator(head);}
    /// @return Iterator to end
    iterator end() {return iterator();}
    /// @return Iterator to end
    const_iterator cend() const {return const_iterator();}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of list
    size_t size() const {return sz;}
    /// @return Does the list contain anything?
    bool empty() const {return sz == 0;}

    /// @brief Resize the list
    /// @param n Size
    /// @param val Value if size is greater of default elements
    ///
    /// If the new size is less than the current progressively remove elements
    /// in the list. Otherwise progressively insert values at the end equal to
    /// \c val.
    void resize(size_t n, const T& val = T()) {
      /// @todo Implement resize (hint: use push_back and pop_back)
	  size_t run=sz;
	
	  if(n>sz)
		  for(size_t i=0;i<n-run;i++)
			  push_back(val);
      if(n<sz)		
		  for(size_t i=0;i<run-n;i++)
			  pop_back();
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @return Element at front of list
    T& front() {return head->t;}
    /// @return Element at front of list
    const T& front() const {return head->t;}
    /// @return Element at back of list
    T& back() {return tail->t;}
    /// @return Element at back of list
    const T& back() const {return tail->t;}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Add element to front of list
    /// @param val Element
    void push_front(const T& val) {
      /// @todo Implement push front (hint: don't forget the case when the list
      ///       is empty) 
    node* temp = new node(val, nullptr, head); //pushes to the front by making a new head and then switching pointers
    if(tail == nullptr)
        tail = temp;
    if(head != nullptr)
        head->prev = temp;
    head = temp;
    sz++;
    }
    /// @brief Remove the first element of the list. Destroy the element as well.
    void pop_front() {
		/// @todo Implement pop front (hint: don't forget the case when the list
		///       becomes empty)
		if(sz==0) //deletes the head and switches pointers
			return;
		node *tmp = head;
		head = head->next;
		if(head != nullptr)
			head->prev = nullptr;
		--sz;
		delete tmp;
    }
    /// @brief Add element to end of list
    /// @param val Element
    void push_back(const T& val) {
      /// @todo Implement push back (hint: don't forget the case when the list
      ///       is empty)
		node* temp = new node(val, tail, nullptr); //pushes to the back by making a new tail and switching some pointers
		if(sz==0)
			head = temp;
		if(tail != nullptr)
			tail->next = temp;
		tail = temp;
		++sz;
		
	  
    }
    /// @brief Remove the last element of the list. Destroy the element as well.
    void pop_back() {
      /// @todo Implement pop back (hint: don't forget the case when the list
      ///       becomes empty)
		if(sz == 0) //deletes the tail and then makes the second to last the new tail.  
			return;
		node *tmp = tail;
		tail = tail->prev;
		if(tail != nullptr)
			tail->next = nullptr;
		--sz;
		delete tmp;
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
    /// @brief Removes all elements
    void clear() {
      /// @todo Implement clear
	  size_t run=sz;
	  for(size_t i=0;i<run;i++)
		  pop_back();
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:
    node* head; ///< Head of list
    node* tail; ///< Tail of list
    size_t sz;  ///< Size of list
};

}

#endif
