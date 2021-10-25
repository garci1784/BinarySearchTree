/****************
Template created by Kazumi Slott
CS311

Your name: ???????
Your programmer number: ?????
Any difficulties?: ??????
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template<class T>
class BST;

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template<class T>  //make it a templare class
class Node
{
  friend BST<T>; //BST wants to access private members of Node
private:
  T el;
  Node* right;
  Node* left;
public:
  Node() {right = left = NULL;}; //default constructor. set right and left to NULL
  Node(const T& e){el = e;}; 
  T getEl() const {return el;} //returns el
};

//Make it a template class
template<class T>
class BST
{
private:
  Node<T>* root; //check stack_L_T.h to see how declared top

  //You will need 10 private functions here.  WHY private?
  void destroy(Node<T>* p); //private function. WHY?
  void insertNodeR(Node<T>* p, const T& e); //private function. WHY?
  void inOrderPrint(Node<T>* p);
  void preOrderPrint(Node<T>* p); //private function. WHY?
  void postOrderPrint(Node<T>* p); //private function. WHY?


 public:
  BST() {root = NULL;} //implement constructor here
  ~BST(); 
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  /*
  int getMaxLength();
  int getMinLength();
  int getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);
  */
};

//implement the member functions in the header if you are making a template class

//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

/**
 * This BST destructor utilizes the destroy function
 * to delete the nodes of the Binary Search Tree.
 */
template<class T>
BST<T>::~BST()
{
  destroy(root);
}

/**
 * This function deletes the nodes of a Binary Search Tree.
 * @p Node to be deleted
 */
template<class T>
void BST<T>::destroy(Node<T>* p) //private function. WHY?
{
  //destroy all nodes
  if (p == NULL)
    return;
  destroy(p->left);
  destroy(p->right);
  delete p;
}

//If you don't know how to make the insert function using recursion, check the following.
//CS211 Lecture Notes on BST – insertNode
//CS211 Lecture recording - Lecture 4/26(Mon) - DLL::deleteFront, BST::insert(), search()

/**
 * This function inserts an element into the binary search tree
 * recursively.
 * @tparam T template type chosen at run time
 * @param e the node to be inserted into the BST
 */
template<class T>
void  BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

/**
 * This function inserts a node into the BST recursively.
 * @tparam T type chosen at run-time
 * @param p root node
 * @param e element node to be inserted
 */
template<class T>
void BST<T>::insertNodeR(Node<T>* p, const T& e) //private function. WHY?
{
  if (p == NULL)
    p = new Node<T>(e);
  else if (e < p->el)
    insertNodeR(p->left, e);
  else // e >= p->el
    insertNodeR(p->right, e);
}

//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
/**
 * This functions inserts a node into the BST
 * using iteration.
 * @tparam T type chosen at run-time
 * @param e node to be inserted
 */
template <class T>
void BST<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>(e);//make a new node.  Check stack_L_T.h to see how you made a new node.
  Node<T>* p = root;
  Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; 
      if(e < parent->el)
	      p = parent->left;
      else //p->el <= e
	      p = parent->right;
    }

  if(parent == NULL) //tree is empty
    root = newNode;
  else if(e < parent->el) //insert a child as the parent's left child
    parent->left = newNode;
  else //parent->el <= e //insert a child as the parent's right child
    parent->right = newNode;
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

/**
 * This function prints the elements of the BsT
 * using in-order-traversal starting at the root
 * node.
 * @tparam T Type of BST
 */
template <class T>
void BST<T>::inOrderPrint()
{
  inOrderPrint(root);
}

/**
 * This function uses in-order traversal of the
 * BST to print the nodes.
 * @tparam T type of the BST
 * @param p root node
 */
template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if (p == NULL)
    return;
  inOrderPrint(p->left);
  cout << p->el << "-->";
  inOrderPrint(p->right);
}

/**
 * This function uses pre-order traversal of the
 * BST to print the nodes starting at the root.
 * @tparam T  type of the BST
 */
template <class T>
void BST<T>::preOrderPrint()
{
  //pre means print parent -> left child -> right child
  preOrderPrint(root);
}


/**
 * This function uses pre-order traversal of the
 * BST to print the nodes starting at the root.
 * @tparam T  type of the BST
 * @param p root node
 */
template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if (p == NULL)
    return;
  cout << p->el << "-->";
  preOrderPrint(p->left);
  preOrderPrint(p->right);
}

/**
 * This function uses post-order traversal of the
 * BST to print the nodes starting at the root.
 */
template <class T>
void BST<T>::postOrderPrint()
{
  //post means left->right->parent last
  postOrderPrint(root);
}

/**
 * This function uses post-order traversal of the
 * BST to print the nodes starting at the root.
 * @tparam T  type of the BST
 * @param p root node
 */
template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if (p == NULL)
    return;
  postOrderPrint(p->left);
  postOrderPrint(p->right);
  cout << p->el << "-->";
}

/*
//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  
}

template <class T>
int BST<T>::getNumNodes(??????) //private function WHY?
{

}
*/

/*
//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{

}

template <class T>
int BST<T>::getMaxLength(???????) //private function. Why?
{

}
*/

/*
template <class T>
int BST<T>::getMinLength()
{
  
}

template <class T>
int BST<T>::getMinLength(?????) //private function. WHY?
{
  
}
*/

/*                                                                                                    
//This function will return the number of even elements
template <class T>                                                                                    
int BST<T>::getEvenNodes()                                                                            
{                                                                                                     
                                                                                                      
}                                                                                                     
                                                                                                      
template <class T>                                                                                    
int BST<T>::getEvenNodes(?????) //private function. WHY?                                              
{                                                                                                     
                                                                                                      
}                                                                                                     
*/


/*
//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
//return the pointer to the node with e
//return NULL if e is not found
template <class T>
Node<T>* BST<T>::searchI(??????)
{
  ???? p = root;

  while(p ??  ????)
    {
    ??????
    }

  Where do you return NULL?  

}
*/

/*
//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
?????? BST<T>::searchR(??????)
{

}

template <class T>
????? BST<T>::searchR(????? p, const T& e) //private function. WHY?
{

}
*/

#endif
