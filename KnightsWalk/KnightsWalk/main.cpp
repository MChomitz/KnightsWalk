/*
		Knight's Walk
		MChomitz - June 18, 2016

		This program will generate knight's walk(s)

		First addition to the program is the BinaryHeap.h file.
			This contains the BinaryHeap class, which is a template class for a binary heap.
			I will use this to help with finding a knights walk.
*/


#include <iostream>
#include "BinaryHeap.h"

int main()
{
	std::cout << "This is the Knight's Walk Program!\n\n";

	std::vector<int*> testVector;

	int* a = new int(14);
	int* b = new int(-1);
	int* c = new int(32);
	int* d = new int(64);
	
	testVector.push_back(a);
	testVector.push_back(b);
	testVector.push_back(c);
	testVector.push_back(d);

	BinaryHeap<int> testTree(testVector);

	std::cout << "The first item on the heap is (should be 64): " << *testTree.peek() << std::endl;

	*d = 0;

	std::cout << "changing the initialized value from 64 to 0\n";
	std::cout << "The first item ono the heap is now: " << *testTree.peek() << std::endl;
	std::cout << "The value for the initialize variable is now: " << *d;


	std::cin.get();
	return 0;
}