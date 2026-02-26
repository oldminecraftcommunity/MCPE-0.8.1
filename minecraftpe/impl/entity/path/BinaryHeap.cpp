#include <entity/path/BinaryHeap.hpp>
#include <entity/path/Node.hpp>
#include <float.h>
#include <string.h>

BinaryHeap::BinaryHeap() {
	this->array = 0;
	this->arraySize = 0;
	this->_init();
}
void BinaryHeap::_init() {
	this->_size = 0;
	this->array = new Node*[1024];
	this->arraySize = 1024;
}
void BinaryHeap::changeCost(Node* a2, float a3) {
	float nodeCost;					 // s14
	int32_t nodePositionInHeapMaybe; // r1

	nodeCost = a2->nodeCost;
	a2->nodeCost = a3;
	nodePositionInHeapMaybe = a2->nodePositionInHeapMaybe;
	if(a3 >= nodeCost) {
		this->downHeap(nodePositionInHeapMaybe);
	} else {
		this->upHeap(nodePositionInHeapMaybe);
	}
}
void BinaryHeap::clear() {
	this->_size = 0;
}
void BinaryHeap::downHeap(int32_t a2) {
	Node* v2;		// r4
	float nodeCost; // s14
	int32_t size;	// r3
	int32_t v5;		// r6
	int32_t v6;		// r5
	Node** array;	// r2
	float v8;		// s15
	Node* v9;		// r3
	Node* v10;		// r7
	float v11;		// s13

	v2 = this->array[a2];
	nodeCost = v2->nodeCost;
	while(1) {
		size = this->_size;
		v5 = 2 * a2 + 1;
		v6 = 2 * a2 + 2;
		if(v5 >= size) {
			break;
		}
		array = this->array;
		if(v6 < size) {
			v9 = array[v6];
			v8 = v9->nodeCost;
		} else {
			v8 = FLT_MAX;
			v9 = 0;
		}
		v10 = array[v5];
		v11 = v10->nodeCost;
		if(v11 >= v8) {
			if(v8 >= nodeCost) {
				break;
			}
			array[a2] = v9;
			v9->nodePositionInHeapMaybe = a2;
			a2 = 2 * a2 + 2;
		} else {
			if(v11 >= nodeCost) {
				break;
			}
			array[a2] = v10;
			v10->nodePositionInHeapMaybe = a2;
			a2 = 2 * a2 + 1;
		}
	}
	this->array[a2] = v2;
	v2->nodePositionInHeapMaybe = a2;
}
void BinaryHeap::insert(Node* a2) {
	int size;  // r2
	int v6;	   // r8
	Node** v7; // r6
	int i;	   // r3
	int v9;	   // r1

	size = this->_size;
	if(size == this->arraySize) {
		v6 = 2 * size;
		v7 = new Node*[v6];
		memset(v7, 0, v6 * sizeof(Node*));
		for(i = 0; i < this->_size; ++i) {
			v7[i] = this->array[i];
		}
		if(this->array) {
			operator delete[](this->array);
		}
		this->array = v7;
		this->arraySize = v6;
	}
	this->array[this->_size] = a2;
	a2->nodePositionInHeapMaybe = this->_size;
	v9 = this->_size;
	this->_size = v9 + 1;
	this->upHeap(v9);
}
bool_t BinaryHeap::isEmpty() {
	return this->_size == 0;
}
Node* BinaryHeap::peek() {
	return *this->array;
}
Node* BinaryHeap::pop() {
	Node** array; // r2
	int32_t v2;	  // r1
	Node* v3;	  // r4
	Node* result; // r0

	array = this->array;
	v2 = this->_size - 1;
	v3 = *this->array;
	this->_size = v2;
	*array = array[v2];
	this->array[this->_size] = 0;
	if(this->_size > 0) {
		this->downHeap(0);
	}
	result = v3;
	v3->nodePositionInHeapMaybe = -1;
	return result;
}
void BinaryHeap::remove(Node* a2) {
	int32_t nodePositionInHeapMaybe; // r5
	Node** array;					 // r2
	int32_t v5;						 // r1
	int32_t v6;						 // r1

	nodePositionInHeapMaybe = a2->nodePositionInHeapMaybe;
	array = this->array;
	v5 = this->_size - 1;
	this->_size = v5;
	array[nodePositionInHeapMaybe] = array[v5];
	this->array[this->_size] = 0;
	v6 = a2->nodePositionInHeapMaybe;
	if(this->_size > v6) {
		if(this->array[v6]->nodeCost >= a2->nodeCost) {
			this->downHeap(v6);
		} else {
			this->upHeap(v6);
		}
	}
	a2->nodePositionInHeapMaybe = -1;
}
int32_t BinaryHeap::size() {
	return this->_size;
}
void BinaryHeap::upHeap(int32_t a2) {
	Node* v2;		// r3
	float nodeCost; // s15
	Node* v4;		// r2

	v2 = this->array[a2];
	nodeCost = v2->nodeCost;
	while(a2 > 0) {
		v4 = this->array[(a2 - 1) >> 1];
		if(nodeCost >= v4->nodeCost) {
			break;
		}
		this->array[a2] = v4;
		v4->nodePositionInHeapMaybe = a2;
		a2 = (a2 - 1) >> 1;
	}
	this->array[a2] = v2;
	v2->nodePositionInHeapMaybe = a2;
}
BinaryHeap::~BinaryHeap() {
	if(this->array) delete[] this->array;
}
