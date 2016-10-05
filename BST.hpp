/*
 * BST.hpp
 */ 

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }

  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ 
  virtual ~BST() {
    clear(); 
    root = nullptr;
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ 
  virtual std::pair<iterator,bool> insert(const Data& item) {
    
    // check if tree exists
    if (!root){
      root = new BSTNode<Data>(item);
      isize++;

      return std::make_pair(iterator(root),true);
    }
    else {
      BSTNode<Data>* cur = root;
    
      // if node has left and/or right child
      while ((cur-> left) || (cur->right)){
        // node has left child and item is less than data
        if (cur->left && item < cur->data){
          cur = cur->left;
        }
        // node doesn't have left child and item is less than data
        else if ((cur->left == nullptr) && (item < cur->data)){
          cur->left = new BSTNode<Data>(item);
          cur->left->parent = cur;
          isize++;
          return std::make_pair(iterator(cur->left), true);
        }
        // node has right child and item is greater than data
        else if (cur->right && item > cur->data){
          cur = cur->right;
        }

        // node doesn't have right child and item is greater than data
        else if ((cur->right == nullptr) && (item > cur->data)){
          cur->right = new BSTNode<Data>(item);
          cur->right->parent = cur;
          isize++;
          return std::make_pair(iterator(cur->right), true);
        }

        // duplicate data
        if (item == cur->data)
          return std::make_pair(iterator(cur), false);
      }

      // handle after exiting the while loop
      // item less than data
      if (item < cur->data){
        cur->left = new BSTNode<Data>(item);
        cur->left->parent = cur;
        isize++;
        return std::make_pair(iterator(cur->left), true);
      }
      // item greater than data
      else if (item > cur->data){
        cur->right = new BSTNode<Data>(item);
        cur->right->parent = cur;
        isize++;
        return std::make_pair(iterator(cur->right), true);
      }
      
      // duplicate data
      if (item == cur->data)
        return std::make_pair(iterator(cur), false);
    
    return std::make_pair(iterator(cur), false);
  }
}

  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ 
  iterator find(const Data& item) const {
    // check if tree exists
    if (root == nullptr)
      return iterator(nullptr);

    // node to find is the root
    if (root-> data == item)
      return iterator(root);

    BSTNode<Data>* cur = root;

    // loop until node is found or node doesn't exist in the tree 
    while (cur->data != item){
      // item less than data
      if (item < cur->data){
	// left child doesn't exist
        if (!(cur->left))
          break;
        else
          cur = cur->left;
      }
      // item is greater than data
      else if (item > cur->data){
	// right child doesn't exist
        if (!(cur->right))
          break;
        else
          cur = cur-> right;
      }
      if (cur->data == item)  // element to find is found
        return iterator(cur);
    }

    // return nullptr
    return end();
  }

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ 
  void clear() {
    BSTNode<Data> *cur = root;
    bool isEmpty = empty();

    // call dealloc if tree has nodes
    if (!isEmpty)
    {
      dealloc(cur); 
    }

    isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const {
    return (root == nullptr);
  }

  /** Return an iterator pointing to the first item in the BST.
   */
  iterator begin() const {
 
    BSTNode<Data>* cur = root;

    // find the smallest data in the tree if tree exists
    if (cur != nullptr) {
      while (cur->left) {
        cur = cur->left;
      }
    }

    return typename BST<Data>::iterator(cur);

  }

  /*
   * Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

/*
 * Helper function:
 */
  private:
    /*
     * Recursively deallocate the nodes in the binary tree
     */
    static void dealloc(BSTNode<Data>* curNode){
      if (curNode != nullptr){
        dealloc(curNode->left);
        dealloc(curNode->right);

        delete curNode;
      }
    }
 };

//end
#endif //BST_HPP
