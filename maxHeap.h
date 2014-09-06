//
// This file contains the definition of the max heap class. Created in Sep 2014.
//

#include "stdafx.h"
#include "dynArray.h"
#include <cmath>

template <class T>
class MaxHeap {
private:
	DynArray<T> *elements;
	void upShift(size_t i);		// Function to shift the element at i up until it's in place
	void downShift(size_t i);	// Function to shift the element at i down until it's in place
	void heapify(size_t r);		// Recursively heapifies the subtree rooted at index r
	
public:
	MaxHeap() : elements(NULL) {}
	MaxHeap(const T* newArray, const size_t numElements);		// Create an heap by heapifying a given array
	void insert(const T& newElement);		// Insert an element
	bool removeMax(T& removedElement);		// Remove the maximum element
	void enumerate();						// List the contents of the heap
};

// The upshift function
template <class T>
void MaxHeap<T>::upShift(size_t i) {
	size_t iParent;
	while (i > 0) {		// Iterate until we reach the root
		// Compute the index of parent
		iParent = std::ceil(double(i) / 2) - 1;

		// If value of parent is smaller, then swap and iterate
		if ((*elements)[iParent] < (*elements)[i]) {
			elements->swap(i, iParent);
			i = iParent;
		}
		else
			return;
	}
}

// The downshift function
template <class T>
void MaxHeap<T>::downShift(size_t i) {
	// The indices for the left and right children
	size_t iLeft = 2 * i + 1;
	size_t iRight = 2 * i + 2;
	size_t iSwap;

	// Iterate until there exists at least one child
	while (iLeft < elements->getSize()) {
		// Comparison with left child
		bool compareLeft = ((*elements)[iLeft] > (*elements)[i]);

		// Check if there exists a right child also
		if (iRight < elements->getSize()) {
			// The comparison with right child
			bool compareRight = ((*elements)[iRight] > (*elements)[i]);

			// Determine the swap depending on comparison
			if (compareLeft && compareRight)		// Both children are greater. 
				iSwap = ((*elements)[iLeft] >= (*elements)[iRight]) ? iLeft : iRight;
			else if (compareLeft)					// Left child is greater but not right child
				iSwap = iLeft;
			else if (compareRight)					// Right child is greater but not left child.
				iSwap = iRight;						
			else									// Neither children are greater
				return;
		}
		else if (compareLeft)		// There is a left child, and it is greater. No right child
			iSwap = iLeft;
		else						// There is a left child, and it is not greater. No right child.
			return;

		// Perform the swap and continue the loop at this point
		elements->swap(i, iSwap);
		i = iSwap;
		iLeft = 2 * i + 1;
		iRight = 2 * i + 2;
	}
}

// The insert function
template <class T>
void MaxHeap<T>::insert(const T& newElement) {
	// Check if the array is not allocated
	if (elements == NULL) {			
		elements = new DynArray<T>;		// Create the array and push the element
		elements->pushBack(newElement);
		return;
	}
	else {			// Insert the element at the end and shift it up until it's in place
		elements->pushBack(newElement);
		upShift(elements->getSize() - 1);
	}
}

// The remove max function
template <class T>
bool MaxHeap<T>::removeMax(T& returnElement) {
	// Check for empty heap
	size_t size = elements->getSize();

	if (size == 0)
		return false;
	else {
		// Assign the first element to the return value
		returnElement = (*elements)[0];

		// Swap the first and last elements
		elements->swap(0, size - 1);

		// Pop the last element
		elements->popBack();

		// Shift the new first element down
		downShift(0);

		// All done
		return true;
	}
}

// The display function
template <class T>
void MaxHeap<T>::enumerate() {
	elements->enumerate();
}

// The constructor given an ordinary array of elements.
template <class T>
MaxHeap<T>::MaxHeap(const T* newArray, const size_t numElements) {
	// Allocate the dynamic array
	elements = new DynArray<T>(newArray, numElements);

	// Heapify the dynamic array
	heapify(0);
}

// The function to heapify a subtree
template <class T>
void MaxHeap<T>::heapify(size_t r) {
	// The roots of the left and right sub-trees
	size_t rLeft = 2 * r + 1, rRight = rLeft + 1;
	
	// Check for a leaf node. Base case in recursion
	if ((rLeft >= elements->getSize()) && (rRight >= elements->getSize()))
		return;

	// There must be a left child at this point, so heapify it
	heapify(rLeft);

	// If there is a right child, heapify that too
	if (rRight < elements->getSize())
		heapify(rRight);

	// Down-shift the root
	downShift(r);

	// All done
	return;
}