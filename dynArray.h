//
// This file defines the class that implements a dynamic array
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cassert>

// The dynamic array class
template <class T>
class DynArray {
private:
	T *elem;
	size_t size, capacity;
	void expand();			// Function to expand the capacity of the array
	static const size_t growthFactor = 2;		// The growth factor for array expansions
	void shrink();			// Function to shrink the array

public:
	DynArray() : elem(NULL), size(0), capacity(0) {}		// The default constructor
	DynArray(const size_t newCapacity);			// Constructor with a new capacity
	DynArray(const T* newArray, const size_t numElements);		// Constructor given an ordinary arraym
	~DynArray() { delete elem; }		// The destructor
	size_t getSize() const { return size; }
	size_t getCapacity() const { return capacity; }
	void pushBack(const T& newElem);
	void popBack();
	void enumerate() const;		// Print the array
	T& operator[](const size_t index);		// The subscript operator overloading
	void swap(const size_t i, const size_t j);		// The function to swap two elements in the array
};

// Constructor given new capacity
template <class T>
DynArray<T>::DynArray(const size_t newCapacity) {
	try {
		elem = new T[newCapacity];
	}
	catch (std::bad_alloc& e) {
		std::cout << e.what() << endl;
		std::cout << "Out of memory. Aborting." << endl;
		std::abort();
	}
	size = 0;
	capacity = newCapacity;
}

// Function to expand the capacity of the array
template <class T>
void DynArray<T>::expand() {
	// Create a new array
	T* newElem;
	try {
		if (capacity == 0)
			newElem = new T;
		else
			newElem = new T[capacity * growthFactor];
	}
	catch (std::bad_alloc& e) {
		std::cout << e.what() << std::endl;
		std::cout << "Out of memory. Aborting." << std::endl;
		std::abort();
	}

	// Copy the elements to the new array
	for (size_t i = 0; i < size; i++)
		newElem[i] = elem[i];

	// Update capacity and elem
	delete elem;
	elem = newElem;
	if (capacity == 0)
		capacity = 1;
	else
		capacity *= growthFactor;
}

// Function to shrink the capacity of the array
template <class T>
void DynArray<T>::shrink() {
	assert(capacity >= 2);		// There should be a minimum for the capacity
	assert(size < std::floor(capacity / 2));	// This should be true when shrink is called

	// The new capacity
	capacity = std::floor(capacity / growthFactor);

	// Assume that the new capacity is greater than 1
	// Allocate a new array half the size
	T *newElem = new T[capacity];

	// Copy the elements, free memory
	for (size_t i = 0; i < size; i++)
		newElem[i] = elem[i];
	delete elem;
	elem = newElem;
}

// The function to add an element at the end
template <class T>
void DynArray<T>::pushBack(const T& newElem) {
	// Expand if needed
	if (size == capacity)
		expand();

	// Insert the object
	elem[size] = newElem;

	// Update size
	size++;
}

// Function to remove an element from the end
template <class T>
void DynArray<T>::popBack() {
	// Check of the array is empty
	if (size == 0) {
		throw std::runtime_error("Attemped popBack() on empty dynamic array.");
	}

	// Reduce size
	size--;

	// Check if you need to shrink
	if (size < std::floor(capacity / 2))
		shrink();
}

// Function to print the array
template <class T>
void DynArray<T>::enumerate() const {
	// Just print
	for (size_t i = 0; i < size; i++)
		std::cout << elem[i] << " ";
	std::cout << std::endl;
}

// The subscript operator overloading
template <class T>
T& DynArray<T>::operator[](const size_t index) {
	// Check if the index is out of bounds
	if ((index < 0) || (index >= size))
		throw std::out_of_range("An index to dynamic array is out of range.");
	else
		return elem[index];
}

// The swap function
template <class T>
void DynArray<T>::swap(const size_t i, const size_t j) {
	// Do an in-place swap
	elem[i] = elem[i] ^ elem[j];	// Bit-wise xor operation
	elem[j] = elem[i] ^ elem[j];
	elem[i] = elem[i] ^ elem[j];
	return;
}

// Constructor given an ordinary array
template <class T>
DynArray<T>::DynArray(const T* newArray, const size_t numElements) {
	// Check for problematic parameters
	if (newArray == NULL)
		throw std::invalid_argument("Null pointer passed to the dynamic array constructor!");
	else if (numElements <= 0)
		throw std::invalid_argument("The number of elements is not positive!");
	else {
		// Allocate new memory
		try {
			elem = new T[numElements];
		}
		catch (std::bad_alloc& e) {
			cout << "Out of memory in dynamic array constructor!" << endl;
			abort();
		}

		// Copy the elements
		for (size_t i = 0; i < numElements; i++)
			elem[i] = newArray[i];

		// Set capacity and size
		capacity = size = numElements;
	}
}