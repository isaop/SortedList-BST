#pragma once
#include "SortedIndexedList.h"
#include<stack>

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	Node* currentNode;
	int current;
	std::stack<int> stack;
public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


