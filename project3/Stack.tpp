#include <stdexcept>

#include "Stack.hpp"

template<class ItemType>
Stack<ItemType>::Stack() 
{
	//starting with nothing in the stack 
} 

template<class ItemType>
Stack<ItemType>::~Stack()
{
	//deletes enirtes on the stack 
	clear();
}

template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	//is the head pointer is nothing reurn true
	return headPtr == nullptr;
}

template<class ItemType>
int Stack<ItemType>::size() const
{
	//gets the current size
	return currentSize;
}

template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	//make a new node with the new item
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem);
    
    //points the node to the next from the stack
    newNodePtr->setNext(headPtr);
    
    //assignes the head pointer and adds to the size 
    headPtr = newNodePtr;
    currentSize++;
	return true;
}

template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	// TODO
	return ItemType();
}

template<class ItemType>
bool Stack<ItemType>::pop() 
{
	// TODO
	return false;
}

template<class ItemType>
void Stack<ItemType>::clear()
{
	// TODO
}

