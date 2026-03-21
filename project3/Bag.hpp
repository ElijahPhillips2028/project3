#ifndef _BAG_HPP
#define _BAG_HPP

#include <vector>

#include "Node.hpp"

template<class ItemType>
class Bag
{
	private:
		Node<ItemType>* headPtr; // Pointer to first node
		int itemCount;           // Current number of items in bag

		/** Private helper function.
		Returns either a pointer to the node containing a given item,
		or the null pointer if the item is not found */
		Node<ItemType>* getPointerTo(const ItemType& target) const;

	public:
		Bag(); 
		~Bag();
		
		Bag(const Bag& b) = delete; // no copy 
		Bag operator=(const Bag& b) = delete; // no copy

		/** Returns the number of items in the bag.
		 * @return The total number of items in the bag. */
		int size() const;
		/** Determines whether this bag is empty.
		 * @return True if the bag has no items, or false if not. */
		bool isEmpty() const;
		/** Adds a new item to the bag.
		 * @param newItem item to be added.
		 * @return True if insert was successful, or false if not.
		 * @post If successful, newEntry is added to the bag,
		 * and the number of items in the bag has increased by 1. */
		bool add(const ItemType& newItem);
		/** Deletes all entries from this bag.
		 *  @post The bag contains no items, and the number of items is 0. */
		void clear();
		/** Tests whether this bag contains a given item.
		 * @param anItem The item to locate.
		 * @return True if bag contains anEntry, or false otherwise. */
		bool contains(const ItemType& anItem) const;
		/** Returns the number of times a given item appears in this bag.
		 * @param anItem The item to locate.
		 * @return The integer number of times the item is in this bag. */
		int getFrequencyOf(const ItemType& anItem) const;
		/** Returns a vector containing the same items that are in this bag.
		 * @return A vector of all items in the bag. */
		std::vector<ItemType> toVector() const;
};

#include "Bag.tpp"

#endif
