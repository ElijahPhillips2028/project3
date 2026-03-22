#include <stdexcept>
#include <iostream>
#include "Stack.hpp"

template<class ItemType>
Stack<ItemType>::Stack() 
{
	//starting with nothing in the stack 
	headPtr = nullptr;
    currentSize = 0;
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
	//gets the  Items of the top pointer
	return headPtr->getItem();
}

template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if (isEmpty()) {
        return false;
    }
	//makes a temporty node to add
	Node<ItemType>* tempNode = headPtr;
	//set the head pointer to the next item
	headPtr = headPtr -> getNext();
	//adding error check
	if (tempNode == nullptr) {
    return false; 
	}
	//make temp nothing delete it then clear it with removeing one from the stack
	tempNode->setNext(nullptr); 
    delete tempNode;
    tempNode = nullptr;
    currentSize--;
	return true;
}

template<class ItemType>
void Stack<ItemType>::clear()
{
	//removes items untill empty
	while(!isEmpty()){
		pop();
	}
}

