/*
		BinaryHeap.h
		MChomitz - June 18, 2016

		This defines a template class, BinaryHeap, which ensures the first item in the heap is the largest:

		Class BinaryHeap
			public
			 constructor, destructor, copy
			 empty		returns true if the heap is empty. false otherwise.
			 size		returns the number of items on the heap
			 peek		returns the value of the top of the heap.
			 push		add new item and store it in the proper location
			 pull		remove the highest value item and rearange the heap
			private
			 vector of references to items in heap
			 PropogateUp	used for pushing, will move a new item up the list depending on its value
			 PropogateDown	used for pulling, will move an item down the list depening on its value
		
		Because this is a template class, the function definitions are also in the header file.

		There is also a function that checks if an input index is even or odd: bHIsEven.
*/

#ifndef BINARY_HEAP_H

#define BINARY_HEAP_H

#include <vector>

bool inline bHIsEven(int number)		// return true if number is even, else false
{
	return (number % 2 == 0);
}

template<class T>
class BinaryHeap
{
public:
	BinaryHeap(const std::vector<T*>& items);		//ctor
	~BinaryHeap();									//dtor
	BinaryHeap(const BinaryHeap& c);				//copy ctor
	BinaryHeap(BinaryHeap&& m);						//move ctor
	BinaryHeap& operator=(const BinaryHeap& c);		//copy ass op
	BinaryHeap& operator=(BinaryHeap&& m);			//move ass op

	bool empty();
	int size();
	const T* peek();
	void push(T* item);
	T* pull();
private:
	std::vector<T*> m_Heap;
	bool propogateUp(int& index);
	bool propogateDown(int& index);
};

template<class T>
BinaryHeap<T>::BinaryHeap(const std::vector<T*>& items)		// ctor
{
	for (int i = 0; i < items.size(); i++)
	{
		push(items[i]);
	}
}

template<class T>
BinaryHeap<T>::~BinaryHeap()								// dtor
{
	for (int i = 0; i < m_Heap.size(); i++)
	{
		delete m_Heap[i];
	}
}

template<class T>
BinaryHeap<T>::BinaryHeap(const BinaryHeap& c) :			// copy ctor
	m_Heap(c.m_Heap.size())	
{
	for (std::size_t i = 0; i < c.m_Heap.size(); i++)
	{
		m_Heap[i] = new T(*c.m_Heap[i])
	}
}

template<class T>
BinaryHeap<T>::BinaryHeap(BinaryHeap&& m) :					// move ctor
	m_Heap(m.m_Heap)
{
	for (int i = 0; i < m.m_Heap.size(); i++)
	{
		m.m_Heap[i] = nullptr;
	}
}

template<class T>
BinaryHeap<T>& BinaryHeap<T>::operator=(const BinaryHeap& c) // copy ass op
{
	BinaryHeap temp(c);
	this* = std::move(temp);
	return this*;
}

template<class T>
BinaryHeap<T>& BinaryHeap<T>::operator=(BinaryHeap&& m)		// move ass op
{
	if (this != &m)
	{
		for (int i = 0; i < m_Heap.size(); i++)
		{
			delete m_Heap[i];
			m_Heap[i] = m.m_Heap[i];
			m.m_Heap[i] = nullptr;
		}
	}
	return this*;
}

template<class T>
bool BinaryHeap<T>::empty()			// returns true if the heap is empty, false otherwise.
{
	return (m_Heap.empty());
}

template<class T>
int BinaryHeap<T>::size()			// returns the number of items on the heap
{
	return m_Heap.size();
}

template<class T>
const T* BinaryHeap<T>::peek()		// returns the first item on the heap, but does not remove it
{
	return m_Heap[0];
}

template<class T>
void BinaryHeap<T>::push(T* item)	// push new items onto the binary heap.
{
	T* newItem = new T(*item);
	m_Heap.push_back(newItem);
	int index = m_Heap.size() - 1;
	while (!propogateUp(index))
	{
	}
}

template<class T>
T* BinaryHeap<T>::pull()			// pull the highest value from the heap, removing it.
{
	if (m_Heap.empty())
	{
		std::cout << "error: Cannot pull from an empty BinaryHeap!";
		return 0;
	}

	T* result = m_Heap[0];
	int index = m_Heap.size() - 1;
	m_Heap[0] = m_Heap[index];
	m_Heap.pop_back();
	index = 0;
	while (!propogateDown(index))
	{ }

	return result;
}

template<class T>
bool BinaryHeap<T>::propogateUp(int& index)	// bring a new item to it's correct location based on its value
{
	int newIndex;	// for checking the item against its parent in the heap

	if (index == 0)	// if at the top of the heap, can't go higher
	{
		return true;
	}

	if (bHIsEven(index)) // if the index is even or odd, it's parent is calculated differently
	{
		newIndex = index / 2 - 1;
	}
	else
	{
		newIndex = (index + 1) / 2 - 1;
	}

	if (*m_Heap[newIndex] >= *m_Heap[index]) // if the parent is greater than the item, it has reached the propoer location
	{
		return true;
	}

	T* temp = m_Heap[newIndex];		// otherwise, swap the item with it's parent, and return false (not finished propogating)
	m_Heap[newIndex] = m_Heap[index];
	m_Heap[index] = temp;
	index = newIndex;
	return false;
}

template<class T>
bool BinaryHeap<T>::propogateDown(int& index)
{
	int leftindex = index * 2 + 1; // calcuate the index of the left and right children
	int rightindex = index * 2 + 2;

	// check that the item hasn't already reached bottom
	if (rightindex >= m_Heap.size())
	{
		if (leftindex >= m_Heap.size())
		{
			return true;
		}

		if (*m_Heap[leftindex] > *m_Heap[index])
		{
			T* temp = m_Heap[leftindex];
			m_Heap[leftindex] = m_Heap[index];
			m_Heap[index] = temp;
			index = leftindex;
			return true;
		}

		return true;
	}
	// if the left child is the greater of the two children, and larger than the index, swap the item with the left child
	if ((*m_Heap[leftindex] > *m_Heap[rightindex]) && (*m_Heap[leftindex] > *m_Heap[index]))
	{
		T* temp = m_Heap[leftindex];
		m_Heap[leftindex] = m_Heap[index];
		m_Heap[index] = temp;
		index = leftindex;
		return false;
	}
	// otherwise, if the right child is larger than the item, then swap with the right child
	if (*m_Heap[rightindex] > *m_Heap[index])
	{
		T* temp = m_Heap[rightindex];
		m_Heap[rightindex] = m_Heap[index];
		m_Heap[index] = temp;
		index = rightindex;
		return false;
	}
	// if neither work, the item is in the correct location
	return true;
}

#endif // !BINARY_HEAP_H
