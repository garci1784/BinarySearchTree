/****************
Template created by Kazumi Slott
CS311

Your name: Jorge Ezequiel Garcia Lopez
Your programmer number: 08
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
  int  getMaxLength(Node<T>* p); //private function. WHY?
  int  getNumNodes(Node<T>* p); //private function. WHY?
  int  getMinLength(Node<T>* p); //private function. WHY?
  int  getEvenNodes(Node<T>* p); //private function. WHY? 
  Node<T>* searchR(Node<T>* p, const T& e); //private function. WHY?


 public:
  BST() {root = NULL;} //implement constructor here
  ~BST(); 
  void insertNodeR(const T& e);
  void insertNodeI(const T& e);
  void inOrderPrint();
  void preOrderPrint();
  void postOrderPrint();
  int  getMaxLength();
  int  getMinLength();
  int  getNumNodes();
  int getEvenNodes();
  Node<T>* searchI(const T& e);
  Node<T>* searchR(const T& e);
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

template<class T>
void  BST<T>::insertNodeR(const T& e)
{
  insertNodeR(root, e);
}

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
      if(e < p->el)
	      p = p->left;
      else //p->el <= e
	      p = p->right;
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

template <class T>
void BST<T>::inOrderPrint()
{
  inOrderPrint(root);
}

template <class T> //private function. WHY?
void BST<T>::inOrderPrint(Node<T>* p)
{
  if (p == NULL)
    return;
  inOrderPrint(p->left);
  cout << p->el << "-->";
  inOrderPrint(p->right);
}

template <class T>
void BST<T>::preOrderPrint()
{
  //pre means print parent -> left child -> right child
  preOrderPrint(root);
}

template <class T>
void BST<T>::preOrderPrint(Node<T>* p) //private function. WHY?
{
  if (p == NULL)
    return;
  cout << p->el << "-->";
  preOrderPrint(p->left);
  preOrderPrint(p->right);
}

template <class T>
void BST<T>::postOrderPrint()
{
  //post means left->right->parent last
  postOrderPrint(root);
}

template <class T>
void BST<T>::postOrderPrint(Node<T>* p) //private function. WHY?
{
  if (p == NULL)
    return;
  postOrderPrint(p->left);
  postOrderPrint(p->right);
  cout << p->el << "-->";
}

//If you don't know how to make this, check the following
//Lec Notes on BST :: Recursive Functions – getNumNodes
//CS211 Lecture recording - Lecture 4/30(Fri) - BST::getNumNodes, phase 3 of college

template <class T>
int BST<T>::getNumNodes()
{
  return getNumNodes(root);
}

template <class T>
int BST<T>::getNumNodes(Node<T>* p) //private function WHY?
{
  if (p == NULL)
    return 0;
  else 
    return getNumNodes(p->left) + getNumNodes(p->right) + 1;
}

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int BST<T>::getMaxLength()
{
  return getMaxLength(root);
}

template <class T>
int BST<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if (p == NULL)
    return 0;
  else
  {
    return max(getMaxLength(p->left), getMaxLength(p->right)) + 1;
  }
}

template <class T>
int BST<T>::getMinLength()
{
  getMinLength(root);
}

template <class T>
int BST<T>::getMinLength(Node<T>* p) //private function. WHY?
{
  if (p == NULL)
    return 0;
  else
  {
    return min(getMinLength(p->left), getMinLength(p->right)) + 1;
  }
}

//This function will return the number of even elements
template <class T>                                                                                    
int BST<T>::getEvenNodes()                                                                            
{                                                                                                     
  return getEvenNodes(root);
}                                                                                                     
                                                                                                      
template <class T>                                                                                    
int BST<T>::getEvenNodes(Node<T>* p) //private function. WHY? 
{
  int count = 0;
  if (p == NULL)
    return 0;
  else
  {
    if ((p->el) % 2 == 0)
      count++;
    return count + getEvenNodes(p->left) + getEvenNodes(p->right);
  }
}                                                                                                     

//Make a search function using iteration. Return the pointer to the node having e
//return NULL if e is not found.
//return the pointer to the node with e
//return NULL if e is not found
template <class T>
Node<T>* BST<T>::searchI(const T& e)
{
  Node<T>* p = root;

  while(p !=  NULL)
    {
      if (p->el == e || p == NULL)
        return p;
      else if (p->el > e)
        p = p->left;
      else // p->el <= e
        p = p->right;
    }

  //Where do you return NULL?  
}

//Make a search function using recursion.
//Return the pointer to the node having e or return NULL if e is not found.
template <class T>
Node<T>* BST<T>::searchR(const T& e)
{
  searchR(root, e);
}

template <class T>
Node<T>* BST<T>::searchR(Node<T>* p, const T& e) //private function. WHY?
{
  // base case
  if (p == NULL || p->el == e)
    return p; // either NULL or location of root
  else if (e < p->el)
    return searchR(p->left, e);
  else
    return searchR(p->right, e);
}

#endif
