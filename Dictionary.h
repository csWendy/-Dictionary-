/*
Author: <Xiaoning Wang>
Course: {235}
Instructor: <Pavel Shostak>
Assignment: <Home Project 3>
*/

#ifndef DICTIONARY_
#define DICTIONARY_
using namespace std;

template <class keyType, class itemType>
class Node
{
private:
	keyType key;
	itemType item;
	Node<keyType, itemType> *left, *right;
public:
	Node();
	Node(const keyType &key, const itemType &item);
	void setLeft(Node<keyType,itemType> *);
 	void setRight(Node<keyType, itemType> *);
 	void setKey(const keyType&);
 	Node<keyType, itemType>* getLeft() const; 
 	Node<keyType, itemType>* getRight() const;
 	keyType& ref_key(); 
 	itemType& ref_item();
 	bool operator == (const Node<keyType, itemType>& a);
	bool operator != (const Node<keyType, itemType>& a);
	bool operator > (const Node<keyType, itemType>& a);
	bool operator < (const Node<keyType, itemType>& a);
	bool operator >= (const Node<keyType, itemType>& a);
	bool operator <= (const Node<keyType, itemType>& a);
};


template <class keyType, class itemType>
class Dictionary
{
private:
	keyType key;
	itemType item;
	Node <keyType, itemType> *root;
	void _clear(Node <keyType, itemType> *cur);
	Node <keyType,itemType>* _balance(Node <keyType, itemType>* itemList, int small, int large);
	void Trav_Inorder(Node<keyType,itemType>* itemList, Node <keyType, itemType>* cur, int &index);
	int _size(Node <keyType, itemType> *subTree);
	int _height(Node<keyType,itemType> *subTree);
	Node <keyType, itemType> * _find(keyType key);
public:
	Dictionary();
	Dictionary(const keyType&);
	bool IsEmpty();
	void Clear();
	int Size();
	int Height();
	int Count(const keyType& ); 
	void Remove(const keyType&);
	void Push_Back(const keyType&, const itemType&);
	void Balance(); 
	itemType& operator[](const keyType&);
	~ Dictionary();
};


#include "Dictionary.cpp"
#endif

