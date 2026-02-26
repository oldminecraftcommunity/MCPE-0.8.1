#pragma once
#include <_types.h>
#include <math/Vec3.hpp>
#include <util/ArrayWithLength.hpp>

struct Node;
struct Entity;

struct Path
{
	Node** nodes;
	int32_t pathSizeMaybe, currentIndex, size;

	Path(arrayWithLength<Node*>);
	Vec3 currentPos(const Entity*);
	Vec3 currentPos();
	bool_t endsIn(Vec3*);
	bool_t endsInXZ(Vec3*);
	Node* get(int32_t);
	int32_t getIndex();
	Vec3 getPos(const Entity*, int32_t);
	int32_t getSize();
	bool_t isDone();
	Node* last();
	void next();
	bool_t sameAs(Path*);
	void setIndex(int32_t);
	void setSize(int32_t);
	~Path();
};
