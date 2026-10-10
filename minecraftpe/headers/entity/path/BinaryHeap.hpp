#pragma once
#include <util/ArrayWithLength.hpp>

struct Node;
struct BinaryHeap
{
	arrayWithLength<Node*> array;
	int32_t _size;

	BinaryHeap();
	void _init();
	void changeCost(Node*, float);
	void clear();
	void downHeap(int32_t);
	void insert(Node*);
	bool_t isEmpty();
	Node* peek();
	Node* pop();
	void remove(Node*);
	int32_t size();
	void upHeap(int32_t);
	~BinaryHeap();
};
