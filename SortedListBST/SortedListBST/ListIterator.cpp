#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
#include<stack>
using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	
	this->first();
	/*this->stack = std::stack<int>{};
	this->first();*/
}//theta(1)

void ListIterator::first(){

	this->current = this->list.root;
	if (!this->stack.empty()) {
		while (!this->stack.empty()) {
			this->stack.pop();
		}
	}
	while (this->current != -1) {
		this->stack.push(this->current);
		current = this->list.tree[this->current].left;
	}
	if (this->stack.empty() == false) {
		this->current = this->stack.top();
	}
	else {
		this->current = -1;
	}
}//theta(n)

void ListIterator::next(){


	if (this->valid() == false) {
		throw std::exception("");
	}
	int node = this->stack.top();
	this->stack.pop();
	if (this->list.tree[node].right != -1) {
		node = this->list.tree[node].right;
		while (node != -1) {
			this->stack.push(node);
			node = this->list.tree[node].left;
		}
	}
	if (stack.empty() == false) {
		this->current = this->stack.top();
	}
	else {
		this->current = -1;
	}
}//theta(n)

bool ListIterator::valid() const{
	
	
	return this->current != -1;
}//theta(1)

TComp ListIterator::getCurrent() const{

	if (this->valid() == true) {
		return this->list.tree[this->current].info;
	}
	else {
		throw std::exception("");
	}
}//theta(1)


