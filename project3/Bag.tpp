#include "Bag.hpp"

template<class ItemType>
Bag<ItemType>::Bag() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
int Bag<ItemType>::size() const
{
	return itemCount;
}

template<class ItemType>
bool Bag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class ItemType>
bool Bag<ItemType>::add(const ItemType& newItem)
{
	// Add to beginning of chain: new node references rest of chain;
	// (headPtr is null if chain is empty)
	Node<ItemType>* nextNodePtr = new Node<ItemType>(newItem, headPtr);

	headPtr = nextNodePtr;          // New node is now first node
	itemCount++;

	return true;                    // The method is always successful
}

template<class ItemType>
void Bag<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();
		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
} 

template<class ItemType>
Node<ItemType>* Bag<ItemType>::getPointerTo(const ItemType& target) const
{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (target == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	}

	return curPtr;
}

template<class ItemType>
bool Bag<ItemType>::contains(const ItemType& anItem) const
{
	return (getPointerTo(anItem) != nullptr);
}

template<class ItemType>
int Bag<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anItem == curPtr->getItem())
		{
			frequency++;
		}

		counter++;
		curPtr = curPtr->getNext();
	}

	return frequency;
}

template<class ItemType>
std::vector<ItemType> Bag<ItemType>::toVector() const
{
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}

	return bagContents;
}

template<class ItemType>
Bag<ItemType>::~Bag()
{
	   clear();
}

