/*
Author: <Xiaoning Wang>
Course: {235}
Instructor: <Pavel Shostak>
Assignment: <Home Project 3>
*/

#include "Dictionary.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

template<class keyType, class itemType>
Node<keyType, itemType>::Node()
{
  left = nullptr;
  right =  nullptr;
}

template<class keyType, class itemType>
Node<keyType, itemType>::Node(const keyType& new_key, const itemType& new_item)
{
  key = new_key;
  item = new_item; 
  left = nullptr;
  right = nullptr;
}

template<class keyType, class itemType>
void Node<keyType, itemType>::setLeft(Node<keyType, itemType>* const new_left) 
{
  left = new_left;
}

template<class keyType, class itemType>
void Node<keyType, itemType>::setRight(Node<keyType, itemType>* const new_right) 
{
  right = new_right;
}

template<class keyType, class itemType>
void Node<keyType, itemType>::setKey(const keyType& new_key) 
{
  key = new_key;
}

template<class keyType, class itemType>
Node<keyType, itemType>* Node<keyType, itemType> :: getLeft() const
{
  return left;
}

template<class keyType, class itemType>
Node<keyType, itemType>* Node<keyType, itemType> :: getRight() const
{
  return right;
}

template<class keyType, class itemType>
keyType& Node<keyType, itemType>::ref_key()
{
  return key;
}

template<class keyType, class itemType>
itemType& Node<keyType, itemType> :: ref_item()
{
  return item;
}

template<class keyType, class itemType>
bool Node<keyType, itemType> :: operator == (const Node <keyType, itemType> & a)
{
  if (key = a.ref_key())
    return true;
  else
    return false;
}

template<class keyType, class itemType>
bool Node<keyType, itemType> :: operator != (const Node <keyType, itemType> & a)
{
  return !(key == a.ref_key());
}

template<class keyType, class itemType>
bool Node<keyType, itemType> :: operator > (const Node <keyType, itemType> & a)
{
  if (key > a.ref_key())
    return true;
  else
    return false;
}

template<class keyType, class itemType>
bool Node<keyType, itemType> :: operator < (const Node <keyType, itemType> & a)
{
    return a.ref_key() > key;
}

template<class keyType, class itemType>
bool Node<keyType, itemType> :: operator >= (const Node <keyType, itemType> & a)
{
    return !(key < a.ref_key());
}

template<class keyType, class itemType>
bool Node<keyType, itemType> :: operator <= (const Node <keyType, itemType> & a)
{
    return !(key > a.ref_key());
}


template <class keyType, class itemType>
Dictionary<keyType, itemType> :: Dictionary()
{
  root = nullptr;
}

template <class keyType, class itemType>
Dictionary<keyType, itemType> :: Dictionary (const keyType& new_key)
{
  key = new_key;
}

template <class keyType, class itemType>
bool Dictionary<keyType, itemType> :: IsEmpty()
{
  if (root == nullptr) return true;
  else 
    return false;
}

template <class keyType, class itemType>
void Dictionary<keyType, itemType> :: Clear()
{
  _clear (root);
  root = nullptr;
}

template <class keyType, class itemType>
void Dictionary<keyType, itemType> :: _clear(Node <keyType, itemType> *cur)
{
  if (cur == nullptr) return;
  _clear (cur -> getLeft());
  _clear (cur -> getRight());
  delete cur;
}

template <class keyType, class itemType>
int Dictionary<keyType, itemType> :: _size(Node <keyType, itemType> *subTree) //return # of items stored in container.
{
  int res = 0;
  if (subTree == nullptr) return 0;
  res += _size(subTree -> getLeft());
  res += _size(subTree -> getRight());
  return res + 1;
}

template <class keyType, class itemType>
int Dictionary <keyType, itemType> :: Size ()
{
 return _size(root);
}


template <class keyType, class itemType>
int Dictionary<keyType, itemType> :: _height(Node<keyType, itemType> *subTree) // return the height of the binary search tree. # of nodes in the longest path.
{
  if (subTree == nullptr) return 0;
  else 
    return 1 + max(_height(subTree -> getLeft()),_height(subTree -> getRight()));
}

template <class keyType, class itemType>
int Dictionary<keyType, itemType> :: Height()
{
  return _height(root);
}

template <class keyType, class itemType>
int Dictionary<keyType, itemType> :: Count(const keyType& key)//
{
  Node<keyType, itemType> *cur = root;
  while (cur != nullptr)
  {
    if (cur -> ref_key() == key) return 1; 
    if (cur -> ref_key() > key) cur = cur -> getLeft();
    else 
      cur = cur -> getRight();
  }
  return 0;
}

template <class keyType, class itemType>
itemType& Dictionary<keyType, itemType> :: operator[](const keyType& key)
{
  Node <keyType, itemType> * cur = root;
  if (root == nullptr)
  {
    root = new Node <keyType, itemType>;
    root -> setKey(key);
    return root -> ref_item();
  }

  while (cur != nullptr)
  {
    if (cur -> ref_key() == key) return cur -> ref_item();
    else if (cur -> ref_key() > key) 
    {
      if (cur -> getLeft() != nullptr) cur = cur -> getLeft();
      else 
      {
        cur -> setLeft(new Node <keyType,itemType>);
        cur -> getLeft() -> setKey(key);
        return cur -> getLeft() -> ref_item();
      }
    }
    else 
    {
      if (cur -> getRight() != nullptr) cur = cur -> getRight();
      else
      {
        cur -> setRight (new Node <keyType, itemType>);
        cur -> getRight() -> setKey(key);
        return cur -> getRight() -> ref_item();
      }
    }
  }
}
 
template <class keyType,class itemType>
void Dictionary <keyType, itemType> :: Remove (const keyType& key)
{
  //bool found = false;
  Node <keyType, itemType> * cur = root, *parentPtr = nullptr; 
  while (cur != nullptr)
  {
    if (cur -> ref_key() == key) 
    {
      //found = true;
      break;
    }

    else 
    {
      parentPtr = cur;
      if (cur -> ref_key() > key) cur = cur -> getLeft();
      else 
        cur = cur -> getRight();
    }
  }

  /*if (!found)
  {
    cout << key << "is not in the tree." << endl;
    return;
  }*/

  // the remove node is a leaf.
  if ((cur -> getLeft() == nullptr)  && (cur -> getRight() == nullptr))
    {
      if (parentPtr -> getLeft() == cur)
        parentPtr -> setLeft(nullptr);
      else 
        parentPtr -> setRight(nullptr);
      delete cur;
      return;
    }

  // the remove node has one child.
  else if ((cur -> getLeft() == nullptr && cur -> getRight() !=nullptr ) || (cur -> getRight() == nullptr && cur -> getLeft() !=nullptr))  
    {
      if (parentPtr -> getLeft() == cur)
      {
        if(cur -> getLeft() != nullptr) 
        {
           parentPtr -> setLeft(cur -> getLeft());
           delete cur;
        }
        else
          parentPtr -> setLeft (cur -> getRight());
          delete cur;
      }

      else 
      {
        if(cur -> getLeft() != nullptr) 
        {
           parentPtr -> setRight(cur -> getLeft());
           delete cur;
        }
        else
          parentPtr -> setRight(cur -> getRight());
          delete cur;
      }
    }

  // the remove node has two children.
  else if((cur -> getLeft() != nullptr) && (cur -> getRight() != nullptr)) 
    {
      //replace the node with the largest node on its left subtree. 
      Node <keyType, itemType> * leftLargest = cur -> getLeft();
      Node <keyType,itemType> *leftLargestParent = nullptr;
      while(leftLargest -> getRight() != nullptr) // find the largest on the left subtree.
      {
        leftLargestParent = leftLargest;
        leftLargest = leftLargest -> getRight();
      }
      cur -> setKey(leftLargest -> ref_key());
      if (leftLargest -> getLeft() == nullptr)// leftLargest is a leaf;
      {
        leftLargestParent -> setRight(nullptr);
        delete leftLargest;
      }
      
      else // leftLargest has one child on its left.
      {
        leftLargestParent -> setRight(leftLargest -> getLeft());
        delete leftLargest;
      }
    }
    return;
}

template <class keyType, class itemType>
Node<keyType, itemType>* Dictionary<keyType, itemType> :: _balance(Node <keyType, itemType>* itemList, int small, int large) //return the pointer of the root.
{
  int mid = (small + large)/2;
  if (small > large) return nullptr;
  Node <keyType, itemType> * newRoot = new Node <keyType, itemType> (itemList[mid].ref_key(), itemList[mid].ref_item());
  newRoot -> setLeft (_balance (itemList, small, (mid - 1)));
  newRoot -> setRight (_balance (itemList,(mid + 1), large));
    return newRoot;
}

template <class keyType, class itemType>
void Dictionary<keyType, itemType> :: Trav_Inorder (Node<keyType,itemType>* itemList, Node <keyType, itemType>* cur, int &index)
{
  if (cur == nullptr) return;
  Trav_Inorder (itemList, cur -> getLeft(),index);
  itemList[index] = *cur;
  index ++;
  Trav_Inorder (itemList, cur -> getRight(), index);
}

template <class keyType, class itemType>
void Dictionary<keyType, itemType> :: Balance()
{
  int index = 0;
  int num = Size();
  Node <keyType, itemType> * itemList = new Node <keyType, itemType> [num];
  Trav_Inorder (itemList, root, index);
  Clear();
  root = _balance (itemList, 0, num -1);
  delete[] itemList;
}


template <class keyType, class itemType>
Dictionary< keyType, itemType> :: ~ Dictionary()
{
  Clear();
}
