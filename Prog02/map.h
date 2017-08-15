#ifndef _MAP_H_
#define _MAP_H_

#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include <iostream>
using std::cout;
namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Map ADT based on C++ map implemented with binary search tree
/// @ingroup MySTL
/// @tparam Key Key type
/// @tparam Value Value type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior.
////////////////////////////////////////////////////////////////////////////////
template<typename Key, typename Value>
class map {

  class node;           ///< Forward declare node class
  template<typename>
    class map_iterator; ///< Forward declare iterator class

  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef Key key_type;      ///< Public access to Key type
    typedef Value mapped_type; ///< Public access to Value type
    typedef std::pair<const key_type, mapped_type>
      value_type;              ///< Entry type
    typedef map_iterator<value_type>
      iterator;                ///< Bidirectional iterator
    typedef map_iterator<const value_type>
      const_iterator;          ///< Const bidirectional iterator
    typedef std::reverse_iterator<iterator>
      reverse_iterator;        ///< Reverse bidirectional iterator
    typedef std::reverse_iterator<const_iterator>
      const_reverse_iterator;  ///< Const reverse bidirectional iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Constructor
    map() : root(new node()), sz(0) {
      root->expand();
    }
    /// @brief Copy constructor
    /// @param m Other map
    map(const map& m) : root(new node(*m.root)), sz(m.sz) {
    }
    /// @brief Destructor
    ~map() {
      delete root;
    }

    /// @brief Copy assignment
    /// @param m Other map
    /// @return Reference to self
    map& operator=(const map& m) {
		if(this != &m) {
			delete root;
			root = new node(*m.root);
			sz = m.sz;
		}
		return *this;
	}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return iterator(root->leftmost());}
    /// @return Iterator to end
    iterator end() {return iterator(root);}
    /// @return Iterator to reverse beginning
    reverse_iterator rbegin() {return reverse_iterator(root);}
    /// @return Iterator to reverse end
    reverse_iterator rend() {return reverse_iterator(root->leftmost());}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return const_iterator(root->leftmost());}
    /// @return Iterator to end
    const_iterator cend() const {return const_iterator(root);}
    /// @return Iterator to reverse beginning
    const_reverse_iterator crbegin() const {return const_reverse_iterator(root);}
    /// @return Iterator to reverse end
    const_reverse_iterator crend() const {return const_reverse_iterator(root->leftmost());}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of map
    size_t size() const {return sz;}
    /// @return Does the map contain anything?
    bool empty() const {return sz == 0;}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function should insert a new
    /// element with that key and return a reference to its mapped value
    /// (constructed through default construction)
    Value& operator[](const Key& k) {
      /// @todo implement at function. Utilize inserter function.
	 node* temp=new node(std::make_pair(k,mapped_type()));
	 std::pair<node*, bool> pair=inserter(temp->value);
     return pair.first->value.second;
    }

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function throws an
    /// \c out_of_range exception.
    Value& at(const Key& k) {
      /// @todo implement at function. Utilize find function.
      //node* temp=finder(k);
	  iterator it=find(k);
	  if(it==end())
		throw std::out_of_range("out of range");
	  return it->second;

    }

    /// @param k Input key
    /// @return Value at given key
    ///
    /// If \c k matches an element in the container, the function will return a
    /// reference to its mapped value.
    ///
    /// If \c k is not found in the container, the function throws an
    /// \c out_of_range exception.
    const Value& at(const Key& k) const {
      /// @todo implement at function. Utilize find function.
	  const_iterator it=find(k);
	  if(it==cend())
		throw std::out_of_range("out of range");
	  return it->second;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Insert element into map, i.e., put(k, v) from the Map ADT
    /// @param v Key, Value pair
    /// @return pair of iterator and bool. Iterator pointing to found element or
    ///         already existing element. bool is true if a new element was
    ///         inserted and false if it existed.
    ///
    /// Insert is the "put(k, v)" function of the Map ADT. Remember that Maps
    /// store unique elements, so if the element existed already it is returned.
    std::pair<iterator, bool> insert(const value_type& v) {
      std::pair<node*, bool> n = inserter(v);
	  return std::make_pair(iterator(n.first), n.second);
    }
    /// @brief Remove element at specified position
    /// @param position Position
    /// @return Position of new location of element which was after eliminated
    ///         one
      iterator erase(const_iterator position) {
      /// @todo Implement erase. Utilize eraser helper.
	   	  node* v=finder((*position).first);
	  if(v->is_external()){
		  cout<<"Non Existent Element";
		  return end();
	  }
	  else{
	  iterator m(eraser(v));
	  return m;
	  } 
    }
    /// @brief Remove element at specified position
    /// @param k Key
    /// @return Number of elements removed (in this case it is at most 1)
    size_t erase(const Key& k) {
      /// @todo Implement erase. Utilize finder and eraser helpers.
	        /// @todo Implement erase. Utilize finder and eraser helpers.
 	  node* v=finder(k);
	  if(v->is_external()){
		  cout<<"Non Existent Element";
		  return 0;
	  }
	  else{
	  eraser(v);
	  return 1;
	  } 
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Operations
    /// @{

    /// @brief Search the container for an element with key \c k
    /// @param k Key
    /// @return Iterator to position if found, end() otherwise
    iterator find(const Key& k) {
      /// @todo Implement find. Utilize the finder helper.
	  node* pos=finder(k);
	  iterator m(pos);
	  if(pos->is_internal()){
		  return m;
	  }
	  else
      return end();
    }

    /// @brief Search the container for an element with key \c k
    /// @param k Key
    /// @return Iterator to position if found, cend() otherwise
    const_iterator find(const Key& k) const {
      /// @todo Implement find. Utilize the finder helper
	    node* pos=finder(k);
	  const_iterator m(pos);
	  if(pos->is_internal()){
		  return m;
	  }
	  else
		return cend();
    }

    /// @brief Count elements with specific keys
    /// @param k Key
    /// @return Count of elements with key \c k
    ///
    /// Because all elements in a map container are unique, the function will
    /// only return 1 or 0.
    size_t count(const Key& k) const {
      /// @todo Implement count. Utilize the find operation.
	  if(finder(k)->is_external()){
	  return 0;
	  }
	  else{
      return 1;
	  }
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Helpers
    /// @{

    /// @brief Utility for finding a node with Key \c k
    /// @param k Key
    /// @return Node pointer to either where node exists or where it should be
    ///         inserted
    ///
    /// Base your algorithm off of Code Fragment 10.9 on page 436
    node* finder(const Key& k) const {
      /// @todo Implement finder helper function
      node * n=root->left;
	  while(n->is_internal() && n->value.first!=k){
		  if(k<n->value.first)
			  n=n->left;
		  else 
			  n=n->right;
	  }
      return n;
    }

    /// @brief Utility for inserting a new node into the data structure.
    /// @param v Key, Value pair
    /// @return pair of node and bool. node pointing to found element or
    ///         already existing element. bool is true if a new element was
    ///         inserted and false if it existed.
    ///
    /// Inserter is the "put(k, v)" function of the Map ADT. Remember that Maps
    /// store unique elements, so if the element existed already it is returned.
    ///
    /// Base you algorithm off of Code Fragment 10.10 on page 436
    ///
    /// Hint: Will need to use functions node::replace and node::expand
    std::pair<node*, bool> inserter(const value_type& v) {
      /// @todo Implement inserter helper function
    	node* pos=finder(v.first);
		if(pos->is_internal()){
			//existing entry
			return std::make_pair(pos, false);
		}
		pos->expand(); 
		pos = pos->replace(v);
		sz++;
		return std::make_pair(pos, true); 
    }

    /// @brief Erase a node from the tree
    /// @param n Node to erase
    /// @return Next inorder successor of \c n in tree
    ///
    /// Base your algorithm off of Code Fragment 10.11 on page 437
    ///
    /// Hint: will need to use functions node::inorder_next, node::replace, and
    /// node::remove_above_external
    node* eraser(node* n) {
      /// @todo Implement eraser helper function
	  node* w;
	  if(n->left->is_external()) 
		w=n->left;
	  else if(n->right->is_external())
		w=n->right;
	  else{
		w=n->inorder_next();
		n = n->replace(w->value);
		sz--;
		return w->left->remove_above_external();
		}
		sz--;
		return w->remove_above_external();
		
	  }
      
    

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Data
    /// @{

    node* root;     ///< Root of binary tree, the root will be a sentinel node
                    ///< for end iterator. root.left is the "true" root for the
                    ///< data
    size_t sz;      ///< Number of nodes

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Internal structure for binary search tree
    ////////////////////////////////////////////////////////////////////////////
    struct node {
      public:

        ////////////////////////////////////////////////////////////////////////
        /// @name Constructors
        /// @{

        /// @brief Constructor
        /// @param v Map entry (Key, Value) pair
        node(const value_type& v = value_type()) :
          value(v), parent(nullptr), left(nullptr), right(nullptr) {}

        /// @brief Copy constructor
        /// @param n node to perform deep copy from
        node(const node& n) : value(n.value), parent(nullptr), left(nullptr), right(nullptr) {
          /// @todo Finish implementation of this copy constructor.
          ///       Hint: left and right are not copied correctly at the moment
		  if(n.is_internal()){
			left = new node(*n.left);
			left->parent=this;
			right = new node(*n.right);
			right->parent=this;
		  }
        }

        /// @brief Copy assignment - Deleted
        /// @param n Other node
        node& operator=(const node& n) = delete;

        /// @brief Destructor
        ~node() {
          /// @todo Implement node destructor
		  parent=nullptr;
		  left=nullptr;
		  right=nullptr;
        }

        /// @}
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        /// @name Modifiers
        /// @{

        /// @brief Replace node with a new node of a different value
        /// @param v New value
        /// @return Pointer to new node
		node* replace(const value_type& v) {
		  node* w = new node(v);
		  w->parent = parent;
		  w->left = left;
		  w->right = right;
		  node* n = this;
		  if(n == parent->left)
			parent->left = w;
		  else
			parent->right = w;
		  if(n->left)
			n->left->parent = w;
		  if(n->right)
			n->right->parent = w;
		  n->left = n->right = nullptr;
		  delete n;
		  return w;
		}

        /// @brief Expand external node to make it internal
        void expand() {
          left = new node;
          right = new node;
          left->parent = this;
          right->parent = this;
        }

        /// @brief Remove above external node, assumes this is external node
        /// @return Sibling of \c n, who is promoted to n's parent's position
        node* remove_above_external() {
          node* par = parent;
          node* sib = this == par->left ? par->right : par->left;
          node* gpar = par->parent;
          if(par == gpar->left)
            gpar->left = sib;
          else
            gpar->right = sib;
          sib->parent = gpar;
          par->left = par->right = nullptr;
          delete this;
          delete par;
          return sib;
        }

        /// @}
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        /// @name Accessors

        /// @return If parent is null return true, else false
        bool is_root() const {return parent == nullptr;}
        /// @return If both children are null return true, else false
        bool is_external() const {return left == nullptr && right == nullptr;}
        /// @return If it is not external then it is internal
        bool is_internal() const {return !is_external();}

        /// @return Leftmost child of this node
        node* leftmost() const {
          const node* n = this;
          while(n->is_internal()) n = n->left;
          return n->parent;
        }

        /// @return Next node in the binary tree according to an inorder
        ///         traversal
        node* inorder_next() {
          //Here, I have a right child, so inorder successor is leftmost child
          //of right subtree
          if(right->is_internal()) {
            return right->leftmost();
          }
          //Otherwise, I am a right child myself and need to find an ancestor
          //who has a right child
          else {
            node* n = this;
            node* w = parent;
            while(n == w->right) {
              n = w;
              w = w->parent;
            }
            return w;
          }
        }

        /// @return Previous node in the binary tree according to an inorder
        ///         traversal
        node* inorder_prev() {
          //Here, I have a left child, so inorder predecessor is rightmost child
          //of left subtree
          if(left->is_internal()) {
            node* n = left;
            while(n->is_internal()) n = n->right;
            return n->parent;
          }
          //Otherwise, I am a left child myself and need to find an ancestor
          //who has a left child
          else {
            node* n = this;
            node* w = parent;
            while(n == w->left) {
              n = w;
              w = w->parent;
            }
            return w;
          }
        }
		
	
		
		

        /// @}
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        /// @name Data
        /// @{

        value_type value; ///< Value is pair(key, value)
        node* parent;     ///< Parent node
        node* left;       ///< Left node
        node* right;      ///< Right node

        /// @}
        ////////////////////////////////////////////////////////////////////////
    };

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Bidirectional iterator for a linked binary tree
    /// @tparam U value_type of map
    ////////////////////////////////////////////////////////////////////////////
    template<typename U>
      class map_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
        public:
          //////////////////////////////////////////////////////////////////////
          /// @name Constructors
          /// @{

          /// @brief Construction
          /// @param v Pointer to position in binary tree
          map_iterator(node* v = NULL) : n(v) {}

          /// @brief Copy construction
          /// @param i Other iterator
          map_iterator(const map_iterator<typename std::remove_const<U>::type>& i) : n(i.n) {}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Comparison
          /// @{

          /// @brief Equality comparison
          /// @param i Iterator
          bool operator==(const map_iterator& i) const {return n == i.n;}
          /// @brief Inequality comparison
          /// @param i Iterator
          bool operator!=(const map_iterator& i) const {return n != i.n;}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Dereference
          /// @{

          /// @brief Dereference operator
          U& operator*() const {return n->value;}
          /// @brief Dereference operator
          U* operator->() const {return &n->value;}

          /// @}
          //////////////////////////////////////////////////////////////////////

          //////////////////////////////////////////////////////////////////////
          /// @name Advancement
          /// @{

          /// @brief Pre-increment
          map_iterator& operator++() {n = n->inorder_next(); return *this;}
          /// @brief Post-increment
          map_iterator operator++(int) {map_iterator tmp(*this); ++(*this); return tmp;}
          /// @brief Pre-decrement
          map_iterator& operator--() {n = n->inorder_prev(); return *this;}
          /// @brief Post-decrement
          map_iterator operator--(int) {map_iterator tmp(*this); --(*this); return tmp;}

          /// @}
          //////////////////////////////////////////////////////////////////////

        private:
          node* n; ///< Map node

          friend class map;
      };

    /// @}
    ////////////////////////////////////////////////////////////////////////////

};

}

#endif
