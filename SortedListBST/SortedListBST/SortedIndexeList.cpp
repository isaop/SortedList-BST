#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {

	this->root = 0;
	this->length = 0;
	this->capacity = 16;
	this->tree = new Node[this->capacity];
	this->firstEmpty = 0;
	for (int i = 0; i < this->capacity ; i++) {
		this->tree[i].left = 2*i;
		this->tree[i].right = 2 * i + 1;

	}
}//theta(this->capacity)

int SortedIndexedList::allocate()
{
	int newElem = this->firstEmpty;
	if (newElem != -1) {
		this->firstEmpty = this->tree[this->firstEmpty].right;
		if (this->firstEmpty != -1) {
			this->tree[this->firstEmpty].left = -1;
		}
		this->tree[newElem].right = -1;
	}
	return newElem;
}//theta(1)

void SortedIndexedList::resize() 
{

	this->capacity *= 2;
	Node* newTree = new Node[capacity];
	for (int i = 0; i < this->capacity / 2; i++)
		newTree[i] = tree[i]; // copyint everything in a new array 
	delete[] this->tree;// delete old array 
	this->tree = newTree;
	for (int i = this->capacity / 2; i < this->capacity; i++) {
		this->tree[i].info = NULL_TCOMP;

		if (i == this->capacity / 2) {
			this->tree[i].parent = -1;
		}
		else {
			this->tree[i].parent = i - 1;
		}

		this->tree[i].left = i + 1;
		if (this->tree[i].left == capacity)
			this->tree[i].left = -1;

		this->tree[i].right = -1;
	}
	this->firstEmpty = this->capacity / 2;
}//theta()

int SortedIndexedList::size() const {
	return this->length;
}//theta(1)

bool SortedIndexedList::isEmpty() const {
	if (this->length == 0) {
		return true;
	}
	else {
		return false;
	}
}//theta(1)



TComp SortedIndexedList::getMinimum(int startingRoot)
{
	int currentN = startingRoot;
	int minimumN = startingRoot;
	TComp minValue;
	while (currentN != -1) {
		minValue = this->tree[currentN].info;
		minimumN = currentN;
		currentN = this->tree[currentN].left;
	}
	return minimumN;
}//theta(log2(n))

TComp SortedIndexedList::getMaximum(int startingRoot)
{
	int currentN = startingRoot;
	int maximumN = startingRoot;
	TComp maxValue;
	while (currentN != -1) {
		maxValue = this->tree[currentN].info;
		maximumN = currentN;
		currentN = this->tree[currentN].right;
	}
	return maximumN;
} //theta(log2(n))


TComp SortedIndexedList::getElement(int i) const{
	return this->tree[i].info;
}//theta(1)


int SortedIndexedList::removeRecursively(int node, TComp e, bool& removed) 
{
	if (node == -1) {
		return node; //if tree is empty
	}
	if (e == this->tree[node].info) {//if we find it 
		removed = true;
		if (this->tree[node].left == -1) { // if we don t have anything on the left
			int rightChild = this->tree[node].right;
			this->tree[node] = Node{};
			return rightChild; 
		}
		else if (this->tree[node].right == -1) { // if we don t have anything on the right
			int leftChild = this->tree[node].left;
			this->tree[node] = Node{};
			return leftChild;
		}
		else { // if we have 2 children
			int maxN = this->getMaximum(this->tree[node].left);//get the maximum from the left
			this->tree[node].info = this->tree[maxN].info;
			this->tree[node].left = this->removeRecursively(this->tree[node].left, this->tree[maxN].info, removed);
		}
	}
	else if (this->rel(e, this->tree[node].info)) { //we go on the left
		this->tree[node].left = this->removeRecursively(this->tree[node].left, e, removed);
	}
	else {// we go on the right
		this->tree[node].right = this->removeRecursively(this->tree[node].right, e, removed);
	}
	return node;
}
//(O(n))


TComp SortedIndexedList::remove(int i) {
	TComp e = this->tree[i].info;
	bool removed = false;
	TComp returnValue = e;
	this->root = this->removeRecursively(this->root, e, removed);
	if (removed) {
		this->length -= 1;
		return returnValue;
	}
	else
		throw std::exception();
	

}//O(n)

int SortedIndexedList::search(TComp e) const {

	int returnValue = -1;
	int currentNode = this->root;
	bool found = false;
	while (currentNode != -1 && found == false)
	{
		if (this->tree[currentNode].info == e)
		{
			found = true;
			returnValue = currentNode;
		}
		else
			if (this->rel(this->tree[currentNode].info , e))
				currentNode = this->tree[currentNode].right;
			else
				currentNode = this->tree[currentNode].left;
	}

	return returnValue;

}//best case : theta(1)
//worst case : theta(n)
//total complexity : O(n)

void SortedIndexedList::add(TComp e) {


	if (this->length == this->capacity) {
		resize();
	}
	if (this->length == 0) 
	{
		this->root = firstEmpty;
		this->tree[this->root].info = e;
		tree[root].right = -1;
		tree[root].left = -1;
		tree[root].parent = -1;
	}
	else
	{
		int i = this->root;
		int aux;
		while (i != -1) {
			if (e == this->tree[i].info) {
				break;
			}
			else
				if (this->rel(e, this->tree[i].info)) 
				{
					aux = i;
					i = tree[i].left;
				}
				else 
					if (this->rel(this->tree[i].info, e))
					{
						aux = i;
						i = tree[i].right;
					}
		}
		if (i == -1) {
			firstEmpty = allocate();
			this->tree[firstEmpty].info = e;
			this->tree[firstEmpty].parent = aux;
			this->tree[firstEmpty].left = -1;
			this->tree[firstEmpty].right = -1;
			if (this->rel(e, this->tree[aux].info)) {
				tree[aux].left = firstEmpty;
			}
			else if (this->rel(this->tree[i].info, e)) {
				tree[aux].right = firstEmpty;
			}
			
		}
		
	}
	this->length++;
}//total complexity : O(n)


ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}//theta(1)

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete[] this->tree;
}//theta(1)

