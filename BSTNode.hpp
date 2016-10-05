#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>


/** This class template defines a node type for the BST container.
 */
 
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION: the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ 
   
  BSTNode<Data>* successor() {    
    BSTNode<Data> *cur = this;

    // Case I: node has right subtree
    if (cur->right != nullptr)
    {
      //  go to next node on the right subtree and find the leftmost node
      cur = cur->right;
      if(cur->left) {
        while (cur->left)
          cur = cur->left;
      }
      // return successor
      return cur;
    }

    // Case II: no right subtree
    else {
      // check if have parent
      if(cur->parent == nullptr)
	return cur;

      //  if left of parent node -> return parent
      if (cur->parent->left == cur){
        return cur->parent;
      }

      //  if right of parent node:
      if (cur->parent->right == cur)
      {
	// go up until node is not right child of parent
        while (cur == cur->parent->right){
          cur = cur->parent;
	
	  // check if parent exists
	  if (cur->parent == nullptr)
	    return nullptr;
        }

	// if cur is left child of parent, return parent
        if (cur->parent->left) {
          return cur->parent;
        }

      }
    }
    return nullptr;
  }
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
