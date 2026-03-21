#ifndef _STACK_HPP
#define _STACK_HPP

#include "Node.hpp"

template<class ItemType>
class Stack
{
private:
	Node<ItemType>* headPtr; // Pointer to first node
	int currentSize;         // Current depth of the stack

public:
	/** Stack constructor */
	Stack();

	/** Stack destructor. Must delete any allocated memory. */
	virtual ~Stack();

	Stack(const Stack& s) = delete; // no copy 
	Stack operator=(const Stack& s) = delete; // no copy

	/** Returns the number of items on the stack.
	 * @return The integer number of items on the stack. */
	int size() const;

	/** Determines whether this stack is empty.
	 * @return True if the stack has no items, or false if not. */
	bool isEmpty() const;

	/** Pushes a new entry onto the top of the stack.
	 * @param newItem  The item to be pushed on top of the stack.
	 * @return  True if push was successful, or false if not.
	 * @post  If successful, newItem is on the top of the stack. */
	bool push(const ItemType& newItem);

	/** Pops the top item off of the stack. 
	 * @return True if successful, or false otherwise (if stack is empty). 
	 * @post The stack size is decreased by 1. */
	bool pop();

	/** Returns the top item off of the stack without removing it.
	 * @return item currently on the top of the stack.
	 * @throws std::logic_error if the stack is empty. */
	ItemType peek() const;

	/** Deletes all entries on the stack.
	 * @post Stack contains no items, and the size of the stack is 0. */
	void clear();
};

#include "Stack.tpp"
#endif

